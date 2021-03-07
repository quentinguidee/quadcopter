#include "interface.h"

#include "../utils/log.h"

void Interface::execute(char code[])
{
    Interface::execute(String(code));
}

void Interface::execute(String code)
{
    Log::info("INTERFACE", code);
    char category = code[1];
    if (category == 'C')
    {
        Interface::move(
            code.substring(2, 2).toInt(),
            code.substring(4, 2).toInt(),
            code.substring(6, 2).toInt(),
            code.substring(8, 2).toInt());
    }
    else if (category == 'D')
    {
        char action = code[2];
        if (action == '0')
        {
            Interface::turnOff();
        }
        else if (action == '1')
        {
            Interface::turnOn();
        }
        else if (action == '2')
        {
            Interface::liftOff();
        }
        else if (action == '3')
        {
            Interface::land();
        }
    }
    else if (category == 'M')
    {
        char action = code[2];
        char motor = atoi(&code[3]);
        if (action == '0')
        {
            Interface::turnOffMotor(motor);
        }
        else if (action == '1')
        {
            Interface::turnOnMotor(motor);
        }
    }
    else if (category == 'W')
    {
        char action = code[2];
        if (action == 'P')
        {
            Interface::ping();
        }
    }
    else if (category == 'S')
    {
        Interface::enableSimulatorMode();
    }
}

void Interface::setup(Drone* drone)
{
    Interface::drone = drone;
}

void Interface::move(int x, int y, int z, int r)
{
    // TODO
}

void Interface::turnOn()
{
    drone->startup();
    drone->getOnOffButton().on();
}

void Interface::turnOff()
{
    // TODO: Check if landed first...
    drone->shutdown();
    drone->getOnOffButton().off();
}

void Interface::liftOff(int height)
{
    // TODO
}

void Interface::land()
{
    // TODO
}

void Interface::ping()
{
    drone->ping();
}

void Interface::turnOnMotor(uint8_t motor)
{
    drone->getMotor(motor).startup();
}

void Interface::turnOffMotor(uint8_t motor)
{
    drone->getMotor(motor).shutdown();
}

void Interface::enableSimulatorMode()
{
    drone->enableSimulatorMode();
}
