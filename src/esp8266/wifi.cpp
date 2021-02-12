#include "wifi.h"

#include <Arduino.h>

Wifi::Wifi() :
    server(AsyncWebServer(80))
{
}

void Wifi::setup()
{
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);

    Serial.begin(115200);

    Serial.println("LOADING…");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Drone AP", "droneaccesspoint");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello, world");
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    server.begin();
}

void Wifi::tick()
{
}
