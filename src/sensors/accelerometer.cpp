#include "accelerometer.h"

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
    angleX = sensor.gyroX();
    angleY = sensor.gyroY();
    angleZ = sensor.gyroZ();
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

    float angleXmin = this->angleX;
    float angleXmax = this->angleX;

    float angleYmin = this->angleY;
    float angleYmax = this->angleY;

    float angleZmin = this->angleZ;
    float angleZmax = this->angleZ;

    for (uint8_t i = 0; i < 20; i++)
    {
        updateAngles();

        if (angleX < angleXmin) angleXmin = angleX;
        if (angleX > angleXmax) angleXmax = angleX;

        if (angleY < angleYmin) angleYmin = angleY;
        if (angleY > angleYmax) angleYmax = angleY;

        if (angleZ < angleZmin) angleZmin = angleZ;
        if (angleZ > angleZmax) angleZmax = angleZ;

        delay(50);
    }

    // TODO: Enhance this. This algorithm doesn't take into account
    // the fact that an extreme value couldn't be accurate.
    // Example: take the median.
    angleXoffset = (angleXmax + angleXmin) / 2;
    angleYoffset = (angleYmax + angleYmin) / 2;
    angleZoffset = (angleZmax + angleZmin) / 2;

    // sensor.magXOffset = -(MAG_X_MAX + MAG_X_MIN) / 2;
    // sensor.magYOffset = -(MAG_Y_MAX + MAG_Y_MIN) / 2;
}
