#include "src/drone.h"
#include "src/settings.h"

Drone* drone = nullptr;

void setup()
{
    drone = new Drone();

    Serial.begin(38400);
    Serial1.begin(38400);

    drone->setup();
}

void loop()
{
    drone->tick();
}
