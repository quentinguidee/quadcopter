#include "src/drone.h"
#include "src/settings.h"
#include "src/tests/static_fire_test.h"

Drone* drone = nullptr;
StaticFireTest* test = nullptr;

void setup()
{
    drone = new Drone();
    test = new StaticFireTest(*drone);

    drone->setup();
    // drone->startup();
}

void loop()
{
    // drone->tick();
    test->tick();
}
