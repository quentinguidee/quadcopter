#include "src/motor.h"
#include "src/settings.h"

void setup()
{
    Motor((uint8_t)ESC_MOTOR_A_PIN);
    Motor((uint8_t)ESC_MOTOR_B_PIN);
    Motor((uint8_t)ESC_MOTOR_C_PIN);
    Motor((uint8_t)ESC_MOTOR_D_PIN);
}

void loop()
{
}
