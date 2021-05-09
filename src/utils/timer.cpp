#include "timer.h"

#include <Arduino.h>

void Timer::reset()
{
    resetTime = millis();
}

bool Timer::exceeded(int delay)
{
    return millis() - resetTime >= delay;
}
