#include "led.h"

#include "../interface/send.h"
#include "../utils/log.h"

Led::Led(uint8_t pin) :
    pin(pin),
    status(none)
{
}

void Led::startup()
{
    pinMode(pin, OUTPUT);
    setStatus(isStarted);
}

void Led::on()
{
    digitalWrite(pin, HIGH);
    setStatus(isOn);
}

void Led::off()
{
    digitalWrite(pin, LOW);
    setStatus(isOff);
}

void Led::setStatus(Status status)
{
    switch (status)
    {
        case isStarted:
            Log::info(String("LED") + pin, "Startup");
            break;
        case isOn:
            Send::ledEnabled(pin);
            Log::info(String("LED") + pin, "Turned on");
            break;
        case isOff:
            Send::ledDisabled(pin);
            Log::info(String("LED") + pin, "Turned off");
            break;
    }
}
