#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

#include "component.h"

class Motor : public Component
{
public:
    enum Status
    {
        off,
        ready,
    };

private:
    uint8_t pin;
    uint8_t id;
    uint16_t speed;
    Servo esc;

    Status status;

public:
    Motor(uint8_t id, uint8_t pin);
    ~Motor();

    void setup();
    void startup();
    void shutdown();

    void tick();

    void setSpeed(uint16_t speed);
    uint16_t getSpeed() { return speed; }

    void setStatus(Status status);
    Status getStatus() { return status; }
};

#endif /* MOTOR_H */
