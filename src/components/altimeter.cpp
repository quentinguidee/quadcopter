#include "altimeter.h"

#include <Arduino.h>

Altimeter::Altimeter() :
    z(0),
    rateZ(0),
    timer(millis())
{
}

void Altimeter::tick()
{
    if (isSimulated())
    {
    }
    else
    {
        z = 0;
        rateZ = 0;
    }

    timer = millis();
}

void Altimeter::forceSetZ(float z)
{
    rateZ = (z - this->z) / (millis() - timer);
    this->z = z;
}
