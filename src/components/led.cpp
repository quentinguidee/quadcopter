#include "led.h"

#include "../interface/send.h"
#include "../interface/simulator.h"
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
    if (isSimulated())
    {
        Simulator::enableLed(pin);
        return;
    }

    digitalWrite(pin, HIGH);

    Log::info(String("LED") + pin, "Turned on");
    Send::ledEnabled(pin);
}

void Led::off()
{
    if (isSimulated())
    {
        Simulator::disableLed(pin);
        return;
    }

    digitalWrite(pin, LOW);

    Log::info(String("LED") + pin, "Turned off");
    Send::ledDisabled(pin);
}

void Led::willEnableSimMode()
{
    off();
}
