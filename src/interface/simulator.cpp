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
        case Settings::LED_MOTOR_A_PIN:
            led = "0";
            break;
        case Settings::LED_MOTOR_B_PIN:
            led = "1";
            break;
        case Settings::LED_MOTOR_C_PIN:
            led = "2";
            break;
        case Settings::LED_MOTOR_D_PIN:
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

void Simulator::sendMotorSpeed(
    uint16_t speedMotorA,
    uint16_t speedMotorB,
    uint16_t speedMotorC,
    uint16_t speedMotorD,
    int deltaTime)
{
    Simulator::send(String("#MS") + speedMotorA + "," + speedMotorB + "," + speedMotorC + "," + speedMotorD + "," + deltaTime);
}
