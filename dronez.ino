#include "src/drone.h"
#include "src/settings.h"

Drone drone;

void setup()
{
    drone = Drone();
    drone.startup();
}

void loop()
{
    drone.tick();
}
