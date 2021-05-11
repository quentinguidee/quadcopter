#include "send.h"

#include "../settings.h"

void Send::message(String message)
{
    Serial.println((String) "#" + message);
}

void Send::ledEnabled(uint8_t pin)
{
    switch (pin)
    {
        case Settings::LED_MOTOR_A_PIN:
            message("L11");
            break;
        case Settings::LED_MOTOR_B_PIN:
            message("L21");
            break;
        case Settings::LED_MOTOR_C_PIN:
            message("L31");
            break;
        case Settings::LED_MOTOR_D_PIN:
            message("L41");
            break;
    }
}

void Send::ledDisabled(uint8_t pin)
{
    switch (pin)
    {
        case Settings::LED_MOTOR_A_PIN:
            message("L10");
            break;
        case Settings::LED_MOTOR_B_PIN:
            message("L20");
            break;
        case Settings::LED_MOTOR_C_PIN:
            message("L30");
            break;
        case Settings::LED_MOTOR_D_PIN:
            message("L40");
            break;
    }
}
