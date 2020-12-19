#include "accelerometer.h"

#include <RunningMedian.h>
#include <Wire.h>

void Accelerometer::setup()
{
    Wire.begin();
    sensor.setWire(&Wire);

    sensor.beginAccel();
    sensor.beginGyro();
    sensor.beginMag();

    calibrate();
}

void Accelerometer::tick()
{
    updateAccelerations();
    updateAngles();
    updateMagneticFields();
}

void Accelerometer::updateAccelerations()
{
    sensor.accelUpdate();
    accelerationX = sensor.accelX();
    accelerationY = sensor.accelY();
    accelerationZ = sensor.accelZ();
    acceleration = sensor.accelSqrt();
}

void Accelerometer::updateAngles()
{
    sensor.gyroUpdate();
    angleSpeedX = sensor.gyroX();
    angleSpeedY = sensor.gyroY();
    angleSpeedZ = sensor.gyroZ();
}

void Accelerometer::updateMagneticFields()
{
    sensor.magUpdate();
    magneticFieldX = sensor.magX();
    magneticFieldY = sensor.magY();
    magneticFieldZ = sensor.magZ();
    horizonDirection = sensor.magHorizDirection();
}

void Accelerometer::calibrate()
{
    updateAngles();

    RunningMedian accelerationsX = RunningMedian(100);
    RunningMedian accelerationsY = RunningMedian(100);
    RunningMedian accelerationsZ = RunningMedian(100);

    RunningMedian anglesX = RunningMedian(100);
    RunningMedian anglesY = RunningMedian(100);
    RunningMedian anglesZ = RunningMedian(100);

    for (uint8_t i = 0; i < 100; i++)
    {
        updateAccelerations();
        updateAngles();

        anglesX.add(angleSpeedX);
        anglesY.add(angleSpeedY);
        anglesZ.add(angleSpeedZ);

        accelerationsX.add(accelerationX);
        accelerationsY.add(accelerationY);
        accelerationsZ.add(accelerationZ);

        delay(10);
    }

    accelerationXoffset = accelerationsX.getMedian();
    accelerationYoffset = accelerationsY.getMedian();
    accelerationZoffset = accelerationsZ.getMedian() + 1;

    angleSpeedXoffset = anglesX.getMedian();
    angleSpeedYoffset = anglesY.getMedian();
    angleSpeedZoffset = anglesZ.getMedian();

    // sensor.magXOffset = -(MAG_X_MAX + MAG_X_MIN) / 2;
    // sensor.magYOffset = -(MAG_Y_MAX + MAG_Y_MIN) / 2;
}
