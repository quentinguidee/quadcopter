#include "drone.h"

Drone::Drone()
{
}

Drone::~Drone()
{
}

void Drone::startup()
{
    for (byte i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].startup();
    }
}

void Drone::shutdown()
{
    for (byte i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
}
