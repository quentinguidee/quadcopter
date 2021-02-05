#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFiEsp.h>

class Wifi
{
public:
    enum Status
    {
        reset,
        waitingConnection,
    };

private:
public:
    Wifi();
    ~Wifi() {}

    void setup();
    void tick();
};

#endif /* WIFI_H */
