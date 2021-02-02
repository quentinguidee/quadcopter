#include "motor.h"

#include "../settings.h"

Motor::Motor(uint8_t pin) :
    pin(pin),
    speed(0)
{
    esc.attach(pin, MIN_ESC_PULSE_WIDTH, MAX_ESC_PULSE_WIDTH);
}

Motor::~Motor()
{
}

void Motor::setup()
{
    if (led != nullptr)
    {
        led->setup();
    }
    setStatus(Status::off);
}

void Motor::startup()
{
    if (led != nullptr)
    {
        led->on();
    }
    setStatus(Status::on);
}

void Motor::shutdown()
{
    if (led != nullptr)
    {
        led->off();
    }
    setStatus(Status::inShutdown);
}

void Motor::tick()
{
    esc.write(speed);
}

/**
 * Define the speed. Between 0 and 1000.
 */
void Motor::setSpeed(uint16_t speed)
{
    this->speed = map(speed, 0, 1000, 0, 180);
}

void Motor::registerLed(Led* led)
{
    this->led = led;
}

void Motor::registerJewelLed(JewelLed* statusLed, uint8_t statusLedID)
{
    this->statusLed = statusLed;
    this->statusLedID = statusLedID;
}

void Motor::setStatus(Status status)
{
    this->status = status;

    if (statusLed != nullptr)
    {
        switch (status)
        {
            case off:
                statusLed->on(statusLedID, RED);
                break;

            case inStartup:
                statusLed->on(statusLedID, ORANGE);
                break;

            case on:
                statusLed->on(statusLedID, GREEN);
                break;

            case inShutdown:
                statusLed->on(statusLedID, ORANGE);
                break;

            case failure:
                statusLed->on(statusLedID, BLUE);
                break;

            default: Serial.println("[WARNING|Motor] Unhandled status case");
        }
    }
}
