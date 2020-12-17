#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

#include "led.h"

class Motor
{
private:
    uint8_t pin;
    int speed;
    Servo esc;
    Led* led = nullptr;

public:
    enum Position
    {
        frontLeft,
        frontRight,
        rearLeft,
        rearRight
    };

    Motor(uint8_t pin);
    ~Motor();

    void setup();
    void startup();
    void shutdown();

    void tick();

    void setSpeed(uint16_t speed);

    void registerLed(Led* led);

    Led* getLed() { return led; }
};

#endif /* MOTOR_H */
