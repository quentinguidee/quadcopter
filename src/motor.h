#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

class Motor
{
private:
    uint8_t pin;
    int value;
    Servo esc;

public:
    Motor(uint8_t pin);
    ~Motor();

    void loop();

    void startup();
    void shutdown();
    void setSpeed();
};

#endif /* MOTOR_H */
