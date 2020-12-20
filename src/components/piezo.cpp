#include "piezo.h"

#include "../settings.h"

Piezo::Piezo(uint8_t pin) :
    pin(pin)
{
}

void Piezo::startup()
{
    on((int*)STARTUP_FREQUENCIES, 100, STARTUP_FREQUENCIES_COUNT);
}

void Piezo::shutdown()
{
    noTone(pin);
    duration = 0;
}

void Piezo::tick()
{
    if (!isOn()) return;

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
    else if (duration > deltaTime)
    {
        tone(pin, frequencies[frequencyIndex]);
    }
    else if (duration <= deltaTime)
    {
        noTone(pin);
        frequencyIndex++;
        if (frequencyIndex < frequenciesCount)
        {
            pause = 50;
            startTimer = millis();
        }
        else
        {
            duration = 0;
        }
    }
}

void Piezo::on(int frequencies[], int duration, uint8_t count, bool force)
{
    if (isOn() && !force) return;

    this->startTimer = millis();
    this->frequencies = frequencies;
    this->frequenciesCount = count;
    this->pause = 0;
    this->frequencyIndex = 0;
    this->duration = duration;
}

bool Piezo::isOn()
{
    return duration != 0;
}
