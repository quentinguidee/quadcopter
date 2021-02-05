#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

#include "jewel_led.h"
#include "led.h"

class Motor
{
public:
    enum Status
    {
        off,
        inStartup,
        on,
        inShutdown,
        failure
    };

private:
    uint8_t pin;
    uint8_t id;
    int speed;
    Servo esc;

    Status status = Status::off;

public:
    Motor(uint8_t id, uint8_t pin);
    ~Motor();

    void setup();
    void startup();
    void shutdown();

    void tick();

    void setSpeed(uint16_t speed);

    void setStatus(Status status);
    Status getStatus() { return status; }
};

#endif /* MOTOR_H */
