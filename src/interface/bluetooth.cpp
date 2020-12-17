#include "bluetooth.h"

void Bluetooth::setup()
{
    Serial.begin(9600);
}

void Bluetooth::tick()
{
    if (Serial.available() > 0)
    {
        int value = Serial.read();
    }
}
