#include "motor.h"

#include "settings.h"

Motor::Motor(uint8_t pin) :
    pin(pin),
    value(0)
{
    esc.attach(pin, MIN_ESC_PULSE_WIDTH, MAX_ESC_PULSE_WIDTH);
}

Motor::~Motor()
{
}

void Motor::loop()
{
    esc.write(value);
}

void Motor::startup()
{
}

void Motor::shutdown()
{
}

void Motor::setSpeed()
{
}
