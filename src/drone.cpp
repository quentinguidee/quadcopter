#include "drone.h"

#include "sensors/accelerometer.h"

Drone::Drone()
{
}

Drone::~Drone()
{
}

void Drone::startup()
{
    Accelerometer::setup();
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

void Drone::tick()
{
    Accelerometer::tick();
    for (byte i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].tick();
    }
}

Motor& Drone::getMotor(Motor::Position position)
{
    return motors[(int)position];
}

Motor& Drone::getMotor(int8_t index)
{
    return motors[index];
}
