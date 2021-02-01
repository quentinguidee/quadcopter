#ifndef JEWEL_LED_H
#define JEWEL_LED_H

#include <Adafruit_NeoPixel.h>

#define N_PIXELS 7

#define BLACK 0x000000
#define WHITE 0xffffff
#define RED 0xbe2d2d
#define ORANGE 0xbe722d
#define GREEN 0x61be2d
#define BLUE 0x2d70be

class JewelLed
{
private:
    Adafruit_NeoPixel pixels;

public:
    JewelLed(uint8_t pin);
    ~JewelLed() {}

    void setup();

    void on(uint8_t led, uint32_t color);
    void off(uint8_t led);
    void off();
};

#endif /* JEWEL_LED_H */
