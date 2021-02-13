#include <ESP8266WiFi.h>

#include "wifi.h"

Wifi* wifi;

void setup()
{
    wifi = new Wifi();
    wifi->setup();
}

void loop()
{
    wifi->tick();
}
