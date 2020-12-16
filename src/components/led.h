#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    uint8_t pin;

public:
    Led(uint8_t pin);
    ~Led() {}

    void setup();

    void on();
    void off();
};

#endif /* LED_H */
