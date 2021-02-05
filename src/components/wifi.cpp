#include "wifi.h"

#include "../utils/log.h"

Wifi::Wifi() :
    status(off)
{
}

void Wifi::setup()
{
    this->status = init;

    Log::info(TAG_WIFI, "Serial init.");

    Serial1.begin(115200);
    Serial1.println("AT+RST");
    WiFi.init(&Serial1);

    if (WiFi.status() == WL_NO_SHIELD)
    {
        Log::error(TAG_WIFI, "No WiFi card installed.");
        this->status = error;
    }
    else
    {
        Log::info(TAG_WIFI, "WiFi serial init done.");
        this->status = connected;
    }
}

void Wifi::tick()
{
}
