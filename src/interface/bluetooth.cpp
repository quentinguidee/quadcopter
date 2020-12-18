#include "bluetooth.h"

void Bluetooth::setup()
{
}

void Bluetooth::tick()
{
    if (Serial.available() > 0)
    {
        int value = Serial.read();
    }
}
