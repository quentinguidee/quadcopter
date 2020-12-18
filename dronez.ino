#include "src/drone.h"
#include "src/settings.h"
#include "src/tests/accelerometer_test.h"
#include "src/tests/static_fire_test.h"

Drone* drone = nullptr;
// StaticFireTest* test = nullptr;
AccelerometerTest* test = nullptr;

void setup()
{
    drone = new Drone();
    // test = new StaticFireTest();
    test = new AccelerometerTest(*drone);

    Serial.begin(38400);
    drone->setup();
    // drone->startup();
    test->setup();
}

void loop()
{
    drone->tick();
    test->tick();
}
