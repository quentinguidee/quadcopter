#include "simulator.h"

#include "../settings.h"

void Simulator::send(String message)
{
    Serial.println(message);
}

void Simulator::callbackSimModeEnabled()
{
    send("#SC");
}

void Simulator::setLed(uint8_t pin, bool on)
{
    String mode = on ? "1" : "0";
    String led;

    switch (pin)
    {
        case LED_MOTOR_A_PIN:
            led = "0";
            break;
        case LED_MOTOR_B_PIN:
            led = "1";
            break;
        case LED_MOTOR_C_PIN:
            led = "2";
            break;
        case LED_MOTOR_D_PIN:
            led = "3";
            break;
        default:
            return;
    }

    send(String("#L") + led + mode);
}

void Simulator::enableLed(uint8_t pin)
{
    Simulator::setLed(pin, true);
}

void Simulator::disableLed(uint8_t pin)
{
    Simulator::setLed(pin, false);
}
