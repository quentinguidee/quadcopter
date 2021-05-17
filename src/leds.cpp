#include "leds.h"

void Leds::startup()
{
    for (size_t i = 0; i < LEDS_COUNT; i++)
    {
        leds[i].startup();
    }
}

void Leds::shutdown()
{
    off();
}

void Leds::on()
{
    for (size_t i = 0; i < LEDS_COUNT; i++)
    {
        leds[i].on();
    }
}

void Leds::off()
{
    for (size_t i = 0; i < LEDS_COUNT; i++)
    {
        leds[i].off();
    }
}
