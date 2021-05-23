#include "altimeter.h"

#include <Arduino.h>

Altimeter::Altimeter() :
    z(1.2), previousZ(1.2),
    rateZ(0),
    timer(millis())
{
}

void Altimeter::tick()
{
    z = 1.2;
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
