#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFiEsp.h>

#define TAG_WIFI "WiFi"

class Wifi
{
public:
    enum Status
    {
        off,
        init,
        connected,
        error,
    };

private:
    Status status;

public:
    Wifi();
    ~Wifi() {}

    void setup();
    void tick();

    Status getStatus() { return status; }
};

#endif /* WIFI_H */
