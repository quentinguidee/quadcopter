#include "interface.h"

void Interface::execute(char code[])
{
    Interface::execute(String(code));
}

void Interface::execute(String code)
{
    char category = code[0];
    if (category == 'C')
    {
        Interface::move(
            code.substring(1, 2).toInt(),
            code.substring(3, 2).toInt(),
            code.substring(5, 2).toInt(),
            code.substring(7, 2).toInt());
    }
    else if (category == 'D')
    {
        char action = code[1];
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
        char action = code[1];
        char motor = atoi(&code[2]);
        if (action == '0')
        {
            Interface::turnOffMotor(motor);
        }
        else if (action == '1')
        {
            Interface::turnOnMotor(motor);
        }
    }
    else if (category == 'P')
    {
        char action = code[1];
        if (action == '0')
        {
            Interface::turnOffPiezo();
        }
        else if (action == '1')
        {
            Interface::turnOnPiezo();
        }
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
}

void Interface::turnOff()
{
    // TODO: Check if landed first...
    drone->shutdown();
}

void Interface::liftOff(int height)
{
    // TODO
}

void Interface::land()
{
    // TODO
}

void Interface::turnOnMotor(uint8_t motor)
{
    drone->getMotor(motor).startup();
}

void Interface::turnOffMotor(uint8_t motor)
{
    drone->getMotor(motor).shutdown();
}

void Interface::turnOnPiezo()
{
    // TODO
}

void Interface::turnOffPiezo()
{
    // TODO
}
