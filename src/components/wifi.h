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
        ready,
        connected,
        error,
    };

private:
    Status status;

    char ssid[6] = "Drone";

    WiFiEspServer server;
    RingBuffer buffer;

public:
    Wifi();
    ~Wifi() {}

    void setup();
    void tickSearch();
    void tick();

    Status getStatus() { return status; }

    void sendResponse(WiFiEspClient client);
};

#endif /* WIFI_H */
