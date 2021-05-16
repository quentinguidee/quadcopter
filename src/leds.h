#ifndef LEDS_H
#define LEDS_H

#include "components/led.h"
#include "settings.h"

class Leds
{
private:
    Led leds[4] = {
        Led(Settings::LED_MOTOR_A_PIN),
        Led(Settings::LED_MOTOR_B_PIN),
        Led(Settings::LED_MOTOR_C_PIN),
        Led(Settings::LED_MOTOR_D_PIN),
    };

public:
    Leds() {}
    ~Leds() {}

    void startup();
    void shutdown();
};

#endif /* LEDS_H */
