#include "led.h"

Led::Led(uint8_t pin) :
    pin(pin)
{
}

void Led::setup()
{
    pinMode(pin, OUTPUT);
}

void Led::on()
{
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    digitalWrite(pin, LOW);
}
