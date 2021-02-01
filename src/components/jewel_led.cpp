#include "jewel_led.h"

JewelLed::JewelLed(uint8_t pin) :
    pixels(N_PIXELS, pin, NEO_RGBW + NEO_KHZ800)
{
}

void JewelLed::setup()
{
    pixels.begin();
    pixels.show();
}

void JewelLed::on(uint8_t led, uint32_t color)
{
    pixels.setPixelColor(led, color);
}

void JewelLed::off(uint8_t led)
{
    pixels.setPixelColor(led, 0, 0, 0);
}

void JewelLed::off()
{
    pixels.clear();
}
