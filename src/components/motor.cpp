#include "motor.h"

#include <Servo.h>

#include "../drone.h"
#include "../interface/send.h"
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

    setStatus(Status::setup);
}

void Motor::startup()
{
    setSpeed(0);
    esc.write(speed);

    setStatus(Status::on);
}

void Motor::shutdown()
{
    setSpeed(0);
    esc.write(speed);

    setStatus(Status::off);
}

void Motor::detach()
{
    esc.detach();
    Log::info(String("MOTOR") + id, "Motor detached");
}

bool Motor::healthy()
{
    if (esc.readMicroseconds() != 1000)
    {
        setStatus(failedToSetup);
        return false;
    }
    return true;
}

void Motor::tick()
{
    esc.write(speed);
    // Log::info(String("MOTOR") + id, String(esc.readMicroseconds()) + " read on pin " + String(pin));
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

    switch (status)
    {
        case Status::setup:
            Send::motorSetup(id);
            Log::info(String("MOTOR") + id, String("Setup on pin ") + pin);
            break;
        case Status::on:
            Send::motorStartup(id);
            Log::info(String("MOTOR") + id, String("STARTUP on pin ") + pin);
            break;
        case Status::off:
            Send::motorShutdown(id);
            Log::info(String("MOTOR") + id, String("SHUTDOWN on pin ") + pin);
            break;
        case Status::failedToSetup:
            Send::motorFailedToSetup(id);
            Log::info(String("MOTOR") + id, String("Motor failed to start on pin ") + pin);
            break;
    }
}
