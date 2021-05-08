#include "accelerometer.h"

#include <RunningMedian.h>
#include <Wire.h>

void Accelerometer::startup()
{
    if (isSimulated())
    {
        delay(500);
        return;
    }

    Wire.begin();
    sensor.setWire(&Wire);

    sensor.beginAccel();
    sensor.beginGyro();
    sensor.beginMag();

    calibrate();
}

void Accelerometer::tick()
{
    if (isSimulated())
    {
        updateAnglesFromAccelerations();
        return;
    }

    updateAccelerations();
    updateAngles();
    updateAnglesFromAccelerations();
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

/**
 * Accelerations have to be updated before.
 */
void Accelerometer::updateAnglesFromAccelerations()
{
    angleXFromAcceleration = atan2(getAccelerationY(), sqrt(pow(getAccelerationX(), 2) + pow(getAccelerationZ(), 2))) * RAD_TO_DEG;
    angleYFromAcceleration = atan2(-getAccelerationX(), sqrt(pow(getAccelerationY(), 2) + pow(getAccelerationZ(), 2))) * RAD_TO_DEG;
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
    uint16_t nExperiments = 100;

    RunningMedian accelerationsX = RunningMedian(nExperiments);
    RunningMedian accelerationsY = RunningMedian(nExperiments);
    RunningMedian accelerationsZ = RunningMedian(nExperiments);

    RunningMedian anglesX = RunningMedian(nExperiments);
    RunningMedian anglesY = RunningMedian(nExperiments);
    RunningMedian anglesZ = RunningMedian(nExperiments);

    for (uint8_t i = 0; i < nExperiments; i++)
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

void Accelerometer::willEnableSimMode()
{
    accelerationX = 0;
    accelerationY = 0;
    accelerationZ = -1;

    angleSpeedX = 0;
    angleSpeedY = 0;
    angleSpeedZ = 0;

    accelerationXoffset = 0;
    accelerationYoffset = 0;
    accelerationZoffset = 1;

    angleSpeedXoffset = 0;
    angleSpeedYoffset = 0;
    angleSpeedZoffset = 0;
}
