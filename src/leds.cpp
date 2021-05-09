#include "leds.h"

void Leds::startup()
{
    for (Led led : leds)
    {
        led.startup();
        led.on();
    }
}

void Leds::enableSimMode()
{
    for (Led led : leds)
    {
        led.enableSimMode();
        led.on();
    }
}
