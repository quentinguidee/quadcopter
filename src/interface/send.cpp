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

void Send::shutdownDone() { message("D0"); }
void Send::startupDone() { message("D1"); }

void Send::startTestMotors() { message("D4"); }
void Send::stopTestMotors() { message("D5"); }

void Send::motorStartup(uint8_t id)
{
    message("M" + String(id + 1) + "1");
}

void Send::motorShutdown(uint8_t id)
{
    message("M" + String(id + 1) + "0");
}

void Send::motorSpeedChanged(uint8_t id, uint16_t speed)
{
    message("M" + String(id + 1) + "S" + speed);
}

void Send::accelerometerStartup()
{
    message("A1");
}

void Send::accelerometerCalibrated()
{
    message("A2");
}

void Send::positionTelemetry(float x, float y, float z)
{
    message((String) "APX" + x + "Y" + y + "Z" + z);
}

void Send::angleTelemetry(float x, float y, float z)
{
    message((String) "AAX" + x + "Y" + y + "Z" + z);
}
