#ifndef LED_H
#define LED_H

#include <Arduino.h>

#include "component.h"

class Led : public Component
{
public:
    enum Status
    {
        none,
        isStarted,
        isOn,
        isOff
    };

private:
    uint8_t pin;

    Status status;
    void setStatus(Led::Status status);

public:
    Led(uint8_t pin);
    ~Led() {}

    void startup();

    void on();
    void off();

    Status getStatus() { return status; }
};

#endif /* LED_H */
