#ifndef JEWEL_LED_H
#define JEWEL_LED_H

#include <Adafruit_NeoPixel.h>

#include "../utils/color.h"

#define N_PIXELS 7

class JewelLed
{
private:
    Adafruit_NeoPixel pixels;

public:
    JewelLed(uint8_t pin);
    ~JewelLed() {}

    void setup();

    void on(uint8_t led, Color color);
    void off(uint8_t led);
    void off();
};

#endif /* JEWEL_LED_H */
