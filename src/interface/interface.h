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

    static void move(int x, int y, int z, int r);

    static void turnOn();
    static void turnOff();
    static void liftOff(int height = 20);
    static void land();

    static void turnOnMotor(uint8_t motor);
    static void turnOffMotor(uint8_t motor);

    static void turnOnPiezo();
    static void turnOffPiezo();
};

#endif /* INTERFACE_H */
