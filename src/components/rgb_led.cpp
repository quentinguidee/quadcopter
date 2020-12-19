#include "rgb_led.h"

RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) :
    redPin(redPin),
    greenPin(greenPin),
    bluePin(bluePin),
    green(0),
    red(0),
    blue(0)
{
}

void RGBLed::setup()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLed::on()
{
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

void RGBLed::off()
{
    analogWrite(redPin, LOW);
    analogWrite(greenPin, LOW);
    analogWrite(bluePin, LOW);
}

void RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue, bool refresh)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    if (refresh) on();
}
