#include "accelerometer_test.h"

AccelerometerTest::AccelerometerTest(Drone &drone) :
    drone(drone)
{
}

void AccelerometerTest::setup()
{
    Serial.begin(115200);
}

void AccelerometerTest::tick()
{
    Serial.println("== Accelerations ==");
    Serial.println(drone.getAccelerometer().getAccelerationX());
    Serial.println(drone.getAccelerometer().getAccelerationY());
    Serial.println(drone.getAccelerometer().getAccelerationZ());

    Serial.println("== Angles ==");
    Serial.println(drone.getAccelerometer().getAngleX());
    Serial.println(drone.getAccelerometer().getAngleY());
    Serial.println(drone.getAccelerometer().getAngleZ());

    Serial.println("== Magnetic field ==");
    Serial.println(drone.getAccelerometer().getMagneticFieldX());
    Serial.println(drone.getAccelerometer().getMagneticFieldY());
    Serial.println(drone.getAccelerometer().getMagneticFieldZ());
}
