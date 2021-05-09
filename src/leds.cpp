#include "leds.h"

void Leds::startup()
{
    for (Led led : leds)
    {
        led.startup();
        led.on();
    }
}

void Leds::shutdown()
{
    for (Led led : leds)
    {
        led.off();
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
