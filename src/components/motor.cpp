#include "motor.h"

#include <Servo.h>

#include "../drone.h"
#include "../interface/send.h"
#include "../interface/simulator.h"
#include "../settings.h"
#include "../utils/color.h"
#include "../utils/log.h"

Motor::Motor(uint8_t id, uint8_t pin) :
    id(id),
    pin(pin),
    speed(0),
    esc(Servo()),
    status(Status::off)
{
}

Motor::~Motor()
{
}

void Motor::setup()
{
    esc.attach(pin, 1000, 2000);
    esc.write(0);

    Log::info(String("MOTOR") + id, String("Setup on pin ") + pin);
}

void Motor::startup()
{
    setSpeed(0);
    esc.write(speed);

    Log::info(String("MOTOR") + id, String("STARTUP on pin ") + pin);
    Send::motorStartup(id);

    setStatus(Status::ready);
}

void Motor::shutdown()
{
    setSpeed(0);
    esc.write(speed);

    Log::info(String("MOTOR") + id, String("SHUTDOWN on pin ") + pin);
    Send::motorShutdown(id);

    setStatus(Status::off);
}

void Motor::tick()
{
    if (!isSimulated())
    {
        esc.write(speed);
        // Log::info(String("MOTOR") + id, String(esc.readMicroseconds()) + " read on pin " + String(pin));
    }
}

/**
 * Define the speed. Between 0 and 180.
 */
void Motor::setSpeed(uint16_t speed)
{
    uint16_t newSpeed = speed;

    if (speed < 0)
        newSpeed = 0;
    else if (speed > 180)
        newSpeed = 180;

    this->speed = newSpeed;

    Send::motorSpeedChanged(id, newSpeed);
}

void Motor::setStatus(Status status)
{
    this->status = status;
}

void Motor::willEnableSimMode()
{
    esc.write(0);
    esc.detach();
    Log::info(String("MOTOR") + id, String("Disarmed on pin ") + pin);
    setStatus(Status::off);
}
