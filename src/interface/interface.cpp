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
    else if (category == 'T')
    {
        char action = code[2];
        if (action == '0')
        {
            char codeChar[100];
            code.remove(0, 3);
            code.toCharArray(codeChar, 100);

            float z = atof(strtok(codeChar, ","));
            float accX = atof(strtok(NULL, ","));
            float accY = atof(strtok(NULL, ","));
            float accZ = atof(strtok(NULL, ","));
            float accAngleX = atof(strtok(NULL, ","));
            float accAngleY = atof(strtok(NULL, ","));
            float accAngleZ = atof(strtok(NULL, ","));

            int result = sscanf(codeChar, "$T0%f,%f,%f,%f,%f,%f,%f", &z, &accX, &accY, &accZ, &accAngleX, &accAngleY, &accAngleZ);
            // Serial.println(String("") + z + " " + accX + " " + accY + " " + accZ + " " + accAngleX + " " + accAngleY + " " + accAngleZ);

            Interface::forceSetPositionSensor(z, accX, accY, accZ, accAngleX, accAngleY, accAngleZ);
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

void Interface::forceSetPositionSensor(
    float z,
    float accX, float accY, float accZ,
    float accAngleX, float accAngleY, float accAngleZ)
{
    Accelerometer& accelerometer = Interface::drone->getAccelerometer();
    Altimeter& altimeter = Interface::drone->getAltimeter();
    Position& position = Interface::drone->getPosition();

    accelerometer.forceSetAccelerationX(accX);
    accelerometer.forceSetAccelerationY(accY);
    accelerometer.forceSetAccelerationZ(accZ);

    accelerometer.forceSetAngleSpeedX(accAngleX);
    accelerometer.forceSetAngleSpeedY(accAngleY);
    accelerometer.forceSetAngleSpeedZ(accAngleZ);

    altimeter.forceSetZ(z);
}

void Interface::turnOn()
{
    drone->getOnOffButton().on();
}

void Interface::turnOff()
{
    // TODO: Check if landed first...
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
