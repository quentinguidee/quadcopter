#include "leds.h"

void Leds::setup()
{
    for (Led led : leds)
    {
        led.setup();
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

void Leds::test()
{
    for (Led led : leds)
    {
        led.test();
    }
}
