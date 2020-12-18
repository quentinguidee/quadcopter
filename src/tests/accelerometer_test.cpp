#include "accelerometer_test.h"

AccelerometerTest::AccelerometerTest(Drone& drone) :
    drone(drone)
{
}

void AccelerometerTest::setup()
{
}

void AccelerometerTest::tick()
{
    Accelerometer& accelerometer = drone.getAccelerometer();

    String accelerations = String() + accelerometer.getAccelerationX() + '\t' + accelerometer.getAccelerationY() + '\t' + accelerometer.getAccelerationZ() + '\t' + accelerometer.getAcceleration();
    String angles = String() + accelerometer.getAngleSpeedX() + '\t' + accelerometer.getAngleSpeedY() + '\t' + accelerometer.getAngleSpeedZ();
    String magneticFields = String() + accelerometer.getMagneticFieldX() + '\t' + accelerometer.getMagneticFieldY() + '\t' + accelerometer.getMagneticFieldZ() + '\t' + accelerometer.getHorizonDirection();

    Serial.println(accelerations + '\t' + angles + '\t' + magneticFields);
}
