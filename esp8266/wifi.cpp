#include "wifi.h"

#include <Arduino.h>

Wifi::Wifi() :
    server(AsyncWebServer(80)),
    tracking(""),
    serialResponseBuffer("")
{
}

void Wifi::setup()
{
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);

    Serial.begin(38400);

    Serial.println("LOADING…");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Drone AP", "droneaccesspoint");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello, world");
    });

    server.on("/motors", HTTP_POST, [](AsyncWebServerRequest *request) {
        String motorID;
        String action;

        if (request->hasParam("id", true))
        {
            motorID = request->getParam("id", true)->value();
        }
        else
        {
            motorID = "ERR";
        }

        if (request->hasParam("action", true))
        {
            action = request->getParam("action", true)->value();
        }
        else
        {
            action = "ERR";
        }

        request->send(200, "application/json", String("{\"id\":\"") + motorID + String("\",\"action\":\"") + action + String("\"}"));

        Serial.println(String("$M") + (action == "on" ? "1" : "0") + motorID);
    });

    server.on("/drone", HTTP_POST, [](AsyncWebServerRequest *request) {
        String action;

        if (request->hasParam("action", true))
        {
            action = request->getParam("action", true)->value();
        }
        else
        {
            action = "ERR";
        }

        request->send(200, "application/json", String("{\"action\":\"") + action + String("\"}"));

        Serial.println(String("$D") + action);
    });

    server.on("/wifi/ping", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "application/json", String("{\"status\":\"") + "unknown" + String("\"}"));

        Serial.println(String("$WP"));
    });

    server.on("/tracking", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "application/json", String("{\"data\":\"") + tracking + String("\"}"));
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    server.begin();
}

void Wifi::tick()
{
    while (Serial.available())
    {
        char c = Serial.read();
        if (c == '\r')
        {
            // nothing
        }
        else if (c == '\n' && serialResponseBuffer != "")
        {
            if (serialResponseBuffer[0] == '@')
            {
                tracking = serialResponseBuffer;
            }
            serialResponseBuffer = "";
            return;
        }
        else
        {
            serialResponseBuffer += c;
        }
    }
}
