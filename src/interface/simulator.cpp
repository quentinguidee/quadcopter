#include "simulator.h"

void Simulator::send(String message)
{
    Serial.println(message);
}

void Simulator::callbackSimModeEnabled()
{
    send("#SC");
}
