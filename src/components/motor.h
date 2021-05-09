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
    int16_t speed;
    Servo esc;

    Status status;

public:
    Motor(uint8_t id, uint8_t pin);
    ~Motor();

    void startup();
    void shutdown();
    void disarm();

    void tick();

    void setSpeed(uint16_t speed);
    int16_t getSpeed() { return speed; }

    void setStatus(Status status);
    Status getStatus() { return status; }

    void willEnableSimMode();
};

#endif /* MOTOR_H */
