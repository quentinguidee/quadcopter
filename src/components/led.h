#ifndef LED_H
#define LED_H

#include <Arduino.h>

#include "component.h"

class Led : public Component
{
private:
    uint8_t pin;

public:
    Led(uint8_t pin);
    ~Led() {}

    void startup();

    void on();
    void off();
};

#endif /* LED_H */
