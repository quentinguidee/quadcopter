#ifndef INTERFACE_H
#define INTERFACE_H

#include <Arduino.h>

#include "../drone.h"

class Interface
{
private:
    inline static Drone* drone = nullptr;

public:
    Interface() {}
    ~Interface() {}

    static void execute(char code[]);
    static void execute(String code);

    static void setup(Drone* drone);

    static void move(float x, float y, float z, float r);
    static void forceSetPositionSensor(
        float z,
        float accX, float accY, float accZ,
        float accAngleX, float accAngleY, float accAngleZ);

    static void turnOn();
    static void turnOff();
    static void liftOff();
    static void landing();
    static void startMotorsTest();
    static void stopMotorsTest();

    static void ping();

    static void turnOnMotor(uint8_t motor);
    static void turnOffMotor(uint8_t motor);
};

#endif /* INTERFACE_H */
