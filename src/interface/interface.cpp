#include "interface.h"

#include "../utils/log.h"
#include "../utils/pid.h"

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
        char codeChar[70];
        code.remove(0, 2);
        code.toCharArray(codeChar, 70);

        float x = atof(strtok(codeChar, ","));
        float y = atof(strtok(NULL, ","));
        float z = atof(strtok(NULL, ","));
        float r = atof(strtok(NULL, ","));

        int result = sscanf(codeChar, "$C%f,%f,%f,%f", &x, &y, &z, &r);

        Interface::move(x, y, z, r);
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
    else if (category == 'P')
    {
        char pidID = code[2];
        char pidConstantKey = code[3];
        float value = code.substring(4, code.length()).toFloat();
        PID* pid;

        switch (pidID)
        {
            case '0': pid = &drone->getFlightController().getPIDAngleX(); break;
            case '1': pid = &drone->getFlightController().getPIDAngleY(); break;
            case '2': pid = &drone->getFlightController().getPIDAngleZ(); break;
            case '3': pid = &drone->getFlightController().getPIDAngleRateX(); break;
            case '4': pid = &drone->getFlightController().getPIDAngleRateY(); break;
            case '5': pid = &drone->getFlightController().getPIDAngleRateZ(); break;
            case '6': pid = &drone->getFlightController().getPIDAltitude(); break;
        }

        switch (pidConstantKey)
        {
            case 'P': pid->setKp(value); break;
            case 'I': pid->setKi(value); break;
            case 'D': pid->setKd(value); break;
        }
    }
}

void Interface::setup(Drone* drone)
{
    Interface::drone = drone;
}

void Interface::move(float x, float y, float z, float r)
{
    FlightController& flightController = drone->getFlightController();
    flightController.setDesiredX(x);
    flightController.setDesiredY(y);
    flightController.setDesiredZ(z);
    flightController.setDesiredR(r);
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

void Interface::liftOff()
{
    Interface::move(0, 0, 1.2, 0);
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
    drone->getMotors().get(motor).startup();
}

void Interface::turnOffMotor(uint8_t motor)
{
    drone->getMotors().get(motor).shutdown();
}

void Interface::enableSimulatorMode()
{
    drone->enableSimulatorMode();
}
