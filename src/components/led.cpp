#include "led.h"

#include "../interface/send.h"
#include "../utils/log.h"

Led::Led(uint8_t pin) :
    pin(pin)
{
}

void Led::startup()
{
    pinMode(pin, OUTPUT);
    setStatus(Status::startup);
}

void Led::on()
{
    digitalWrite(pin, HIGH);
    setStatus(Status::on);
}

void Led::off()
{
    digitalWrite(pin, LOW);
    setStatus(Status::off);
}

void Led::setStatus(Status status)
{
    switch (status)
    {
        case Status::startup:
            Log::info(String("LED") + pin, "Startup");
            break;
        case Status::on:
            Send::ledEnabled(pin);
            Log::info(String("LED") + pin, "Turned on");
            break;
        case Status::off:
            Send::ledDisabled(pin);
            Log::info(String("LED") + pin, "Turned off");
            break;
    }
}
