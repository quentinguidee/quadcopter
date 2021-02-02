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
    int speed;
    Servo esc;

    Led* led = nullptr;
    JewelLed* statusLed = nullptr;
    uint8_t statusLedID;

    Status status = Status::off;

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
    void registerJewelLed(JewelLed* statusLed, uint8_t statusLedID);

    Led* getLed() { return led; }

    void setStatus(Status status);
};

#endif /* MOTOR_H */
