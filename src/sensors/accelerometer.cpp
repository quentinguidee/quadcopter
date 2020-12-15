#include "accelerometer.h"

#include <Wire.h>

void Accelerometer::setup()
{
    Wire.begin();
    sensor.setWire(&Wire);

    sensor.beginAccel();
    sensor.beginGyro();
    sensor.beginMag();
}

void Accelerometer::tick()
{
    sensor.accelUpdate();
    accelerationX = sensor.accelX();
    accelerationY = sensor.accelY();
    accelerationZ = sensor.accelZ();
    acceleration = sensor.accelSqrt();

    sensor.gyroUpdate();
    angleX = sensor.gyroX();
    angleY = sensor.gyroY();
    angleZ = sensor.gyroZ();

    Serial.begin(115200);
    sensor.magUpdate();
    magneticFieldX = sensor.magX();
    magneticFieldY = sensor.magY();
    magneticFieldZ = sensor.magZ();
    horizonDirection = sensor.magHorizDirection();
}
