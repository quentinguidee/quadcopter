#include "wifi.h"

#include "../utils/log.h"

Wifi::Wifi() :
    status(off),
    server(WiFiEspServer(80)),
    buffer(RingBuffer(8))
{
}

void Wifi::setup()
{
    this->status = init;

    Log::info(TAG_WIFI, "Serial init.");

    Serial1.begin(115200);
    WiFi.init(&Serial1);
    WiFi.reset();

    if (WiFi.status() == WL_NO_SHIELD)
    {
        Log::error(TAG_WIFI, "No WiFi card installed.");
        this->status = error;
    }
    else
    {
        Log::info(TAG_WIFI, "WiFi serial init done.");
        WiFi.configAP(IPAddress(192, 168, 1, 1));
        WiFi.beginAP(ssid);
        server.begin();
        this->status = ready;
    }
}

void Wifi::tick()
{
    WiFiEspClient client = server.available();
    if (client)
    {
        char
    }
}

void Wifi::sendResponse(WiFiEspClient client)
{
    client.print(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n");
    client.print("Drone connected!\r\n");
}
