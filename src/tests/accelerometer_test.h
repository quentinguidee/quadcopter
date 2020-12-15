#ifndef ACCELEROMETER_TEST_H
#define ACCELEROMETER_TEST_H

#include "../drone.h"

class AccelerometerTest
{
private:
    Drone &drone;

public:
    AccelerometerTest(Drone &drone);
    ~AccelerometerTest() {}

    void setup();
    void tick();
};

#endif /* ACCELEROMETER_TEST_H */
