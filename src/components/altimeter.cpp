#include "altimeter.h"

#include <Arduino.h>

Altimeter::Altimeter() :
    z(0), previousZ(0),
    rateZ(0),
    timer(millis())
{
}

void Altimeter::tick()
{
    z = 0;
    computeRateZ();
    timer = millis();
}

void Altimeter::forceSetZ(float z)
{
    this->previousZ = this->z;
    this->z = z;
}

void Altimeter::computeRateZ()
{
    rateZ = (z - previousZ) / (millis() - timer);
}
