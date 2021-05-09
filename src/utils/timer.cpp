#include "timer.h"

#include <Arduino.h>

void Timer::start()
{
    startTime = millis();
}

bool Timer::exceeded(int delay)
{
    return millis() - startTime >= delay;
}
