#include "led.h"

#include "../interface/simulator.h"

Led::Led(uint8_t pin) :
    pin(pin)
{
}

void Led::startup()
{
    pinMode(pin, OUTPUT);
}

void Led::on()
{
    if (isSimulated())
    {
        Simulator::enableLed(pin);
        return;
    }

    digitalWrite(pin, HIGH);
}

void Led::off()
{
    if (isSimulated())
    {
        Simulator::disableLed(pin);
        return;
    }

    digitalWrite(pin, LOW);
}

void Led::willEnableSimMode()
{
    off();
}
