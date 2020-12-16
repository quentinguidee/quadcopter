#include "motor.h"

#include "../settings.h"

Motor::Motor(uint8_t pin) :
    pin(pin),
    speed(0)
{
    esc.attach(pin, MIN_ESC_PULSE_WIDTH, MAX_ESC_PULSE_WIDTH);
}

Motor::~Motor()
{
}

void Motor::startup()
{
}

void Motor::shutdown()
{
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
