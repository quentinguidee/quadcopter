#include "motors.h"

void Motors::setup()
{
    for (Motor motor : motors) motor.setup();
}

void Motors::startup()
{
    for (Motor motor : motors) motor.startup();
}

void Motors::shutdown()
{
    for (Motor motor : motors) motor.shutdown();
}

void Motors::tick()
{
    for (Motor motor : motors) motor.tick();
}

void Motors::enableSimMode()
{
    for (Motor motor : motors) motor.enableSimMode();
}

Motor& Motors::get(uint8_t i)
{
    return motors[i];
}
