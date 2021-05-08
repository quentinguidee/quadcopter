#ifndef MOTORS_H
#define MOTORS_H

#include "components/motor.h"
#include "settings.h"

class Motors
{
private:
    Motor motors[4] = {
        Motor(0, (uint8_t)Settings::ESC_MOTOR_A_PIN),
        Motor(1, (uint8_t)Settings::ESC_MOTOR_B_PIN),
        Motor(2, (uint8_t)Settings::ESC_MOTOR_C_PIN),
        Motor(3, (uint8_t)Settings::ESC_MOTOR_D_PIN),
    };

public:
    Motors() {}
    ~Motors() {}

    void setup();
    void startup();
    void shutdown();

    void tick();

    void enableSimMode();

    Motor& get(uint8_t i);
};

#endif /* MOTORS_H */
