#include "piezo.h"

#include "../settings.h"

Piezo::Piezo(uint8_t pin) :
    pin(pin)
{
}

void Piezo::startup()
{
    deleteFrequencies();
    on(new int[5]{523, 887, 887, 523, 1046}, 100, 5);
}

void Piezo::shutdown()
{
    noTone(pin);
    duration = 0;
    pause = 0;
    deleteFrequencies();
}

void Piezo::tick()
{
    if (!isOn())
    {
        noTone(pin);
        return;
    }

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
            deleteFrequencies();
        }
    }
}

void Piezo::on(int frequencies[], int duration, uint8_t count, bool force)
{
    if (isOn() && !force)
    {
        delete[] frequencies;
        return;
    }

    if (force) deleteFrequencies();

    this->startTimer = millis();
    this->frequencies = frequencies;
    this->frequenciesCount = count;
    this->pause = 0;
    this->frequencyIndex = 0;
    this->duration = duration;
}

void Piezo::deleteFrequencies()
{
    if (frequencies != nullptr)
    {
        delete[] frequencies;
        frequencies = nullptr;
    }
}

bool Piezo::isOn()
{
    return duration != 0;
}
