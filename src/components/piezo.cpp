#include "piezo.h"

#include "../settings.h"

Piezo::Piezo(uint8_t pin) :
    pin(pin)
{
}

void Piezo::setup()
{
    inStartup = true;
    frequency = STARTUP_FREQUENCIES[0];
    startTimer = millis();
    period = 100;
    repeat = STARTUP_FREQUENCIES_COUNT;
}

void Piezo::tick()
{
    if (period == 0) return;

    currentTimer = millis();
    unsigned long deltaTime = currentTimer - startTimer;

    if (pause != 0)
    {
        if (pause < deltaTime)
        {
            pause = 0;
            startTimer = millis();
        }
    }
    else if (period > deltaTime)
    {
        tone(PIEZO_PIN, frequency);
    }
    else if (period <= deltaTime)
    {
        noTone(PIEZO_PIN);
        repeat--;
        if (repeat > 0)
        {
            pause = 50;
            startTimer = millis();
            if (inStartup) frequency = STARTUP_FREQUENCIES[STARTUP_FREQUENCIES_COUNT - repeat];
        }
        else
        {
            period = 0;
            inStartup = false;
        }
    }
}

void Piezo::on(int frequency, int duration, int repeat)
{
    this->startTimer = millis();
    this->frequency = frequency;
    this->period = duration;
    this->repeat = repeat;
}
