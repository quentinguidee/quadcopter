#include "motor.h"

#include "../settings.h"
#include "../utils/color.h"
#include "../utils/log.h"

Motor::Motor(uint8_t id, uint8_t pin) :
    id(id),
    pin(pin),
    speed(0),
    status(Status::off)
{
}

Motor::~Motor()
{
}

void Motor::setup()
{
    esc.attach(pin, MIN_ESC_PULSE_WIDTH, MAX_ESC_PULSE_WIDTH);
    esc.write(0);
    Log::info(String("MOTOR") + id, String("SETUP on pin ") + pin);
    setStatus(Status::off);
}

void Motor::startup()
{
    setStatus(Status::on);
    setSpeed(25);
    Log::info(String("MOTOR") + id, "STARTUP on pin " + String(pin));
}

void Motor::shutdown()
{
    setStatus(Status::off);
    setSpeed(0);
    Log::info(String("MOTOR") + id, "SHUTDOWN on pin " + String(pin));
}

void Motor::tick()
{
    esc.write(speed);
    Log::info(String("MOTOR") + id, String(esc.read()) + " read on pin " + String(pin));
}

/**
 * Define the speed. Between 0 and 180.
 */
void Motor::setSpeed(uint16_t speed)
{
    this->speed = speed;
}

void Motor::setStatus(Status status)
{
    this->status = status;
}
