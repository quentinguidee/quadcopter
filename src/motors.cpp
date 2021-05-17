#include "motors.h"

/*
For a really strange reason,

for (size_t i = 0; i < 4; i++)

works, but

for (Motor motor : motors)

doesn't. Technically it works, it logs things,
but the ESC calibration is failed.
If you know why, don't hesitate to open an issue;
very curious...
*/

void Motors::setup()
{
    for (size_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].setup();
    }
}

void Motors::startup()
{
    for (size_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].startup();
    }
}

void Motors::shutdown()
{
    for (size_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
}

void Motors::tick()
{
    for (size_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].tick();
    }
}

Motor& Motors::get(uint8_t i)
{
    return motors[i];
}
