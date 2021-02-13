#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

class Wifi
{
private:
    AsyncWebServer server;

public:
    Wifi();
    ~Wifi() {}

    void setup();
    void tick();
};

#endif /* WIFI_H */
