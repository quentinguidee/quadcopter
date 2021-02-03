#include "jewel_led.h"

JewelLed::JewelLed(uint8_t pin) :
    pixels(N_PIXELS, pin, NEO_GRBW + NEO_KHZ800)
{
}

void JewelLed::setup()
{
    pixels.begin();
    pixels.clear();
    pixels.show();
}

void JewelLed::on(uint8_t led, Color color)
{
    switch (color)
    {
        case red:
            pixels.setPixelColor(led, 255, 0, 0, 0);
            break;

        case orange:
            pixels.setPixelColor(led, 255, 40, 0, 0);
            break;

        case green:
            pixels.setPixelColor(led, 0, 255, 0, 0);
            break;

        case blue:
            pixels.setPixelColor(led, 0, 0, 255, 0);
            break;
    }
    pixels.show();
}

void JewelLed::off(uint8_t led)
{
    pixels.setPixelColor(led, 0, 0, 0);
    pixels.show();
}

void JewelLed::off()
{
    pixels.clear();
}
