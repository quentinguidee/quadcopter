#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

class Motor
{
private:
    uint8_t pin;
    int speed;
    Servo esc;

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

    void startup();
    void shutdown();

    void tick();

    void setSpeed(uint16_t speed);
};

#endif /* MOTOR_H */
