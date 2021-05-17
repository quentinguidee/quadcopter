#ifndef LEDS_H
#define LEDS_H

#include "components/led.h"
#include "settings.h"

#define LEDS_COUNT 4

class Leds
{
private:
    Led leds[LEDS_COUNT] = {
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

    void on();
    void off();
};

#endif /* LEDS_H */
