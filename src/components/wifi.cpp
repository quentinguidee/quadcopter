#include "wifi.h"

Wifi::Wifi()
{
}

void Wifi::setup()
{
    Serial.println("[INFO|WiFi] WiFi serial init.");

    Serial1.begin(115200);
    Serial1.println("AT+RST");
    WiFi.init(&Serial1);

    if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println("[FATAL_ERROR|WiFi] No WiFi card installed.");
    }
    else
    {
        Serial.println("[INFO|WiFi] WiFi serial init done.");
        Serial.print("[INFO|WiFi] - IP: ");
        Serial.println(WiFi.localIP());
    }
}

void Wifi::tick()
{
}
