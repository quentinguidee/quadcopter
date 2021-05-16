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
    Log::info(String("LED") + pin, "Startup");
}

void Led::on()
{
    digitalWrite(pin, HIGH);

    Log::info(String("LED") + pin, "Turned on");
    Send::ledEnabled(pin);
}

void Led::off()
{
    digitalWrite(pin, LOW);

    Log::info(String("LED") + pin, "Turned off");
    Send::ledDisabled(pin);
}
