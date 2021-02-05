#include "motor.h"

#include "../settings.h"
#include "../utils/color.h"

Motor::Motor(uint8_t id, uint8_t pin) :
    id(id),
    pin(pin),
    speed(0)
{
    esc.attach(pin, MIN_ESC_PULSE_WIDTH, MAX_ESC_PULSE_WIDTH);
}

Motor::~Motor()
{
}

void Motor::setup()
{
    setStatus(Status::off);
}

void Motor::startup()
{
    setStatus(Status::on);
}

void Motor::shutdown()
{
    setStatus(Status::off);
}

void Motor::tick()
{
    esc.write(speed);
}

/**
 * Define the speed. Between 0 and 1000.
 */
void Motor::setSpeed(uint16_t speed)
{
    this->speed = map(speed, 0, 1000, 0, 180);
}

void Motor::setStatus(Status status)
{
    this->status = status;
}
