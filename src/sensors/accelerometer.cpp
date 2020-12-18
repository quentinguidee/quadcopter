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

    float angleSpeedXmin = this->angleSpeedX;
    float angleSpeedXmax = this->angleSpeedX;

    float angleSpeedYmin = this->angleSpeedY;
    float angleSpeedYmax = this->angleSpeedY;

    float angleSpeedZmin = this->angleSpeedZ;
    float angleSpeedZmax = this->angleSpeedZ;

    for (uint8_t i = 0; i < 20; i++)
    {
        updateAngles();

        if (angleSpeedX < angleSpeedXmin) angleSpeedXmin = angleSpeedX;
        if (angleSpeedX > angleSpeedXmax) angleSpeedXmax = angleSpeedX;

        if (angleSpeedY < angleSpeedYmin) angleSpeedYmin = angleSpeedY;
        if (angleSpeedY > angleSpeedYmax) angleSpeedYmax = angleSpeedY;

        if (angleSpeedZ < angleSpeedZmin) angleSpeedZmin = angleSpeedZ;
        if (angleSpeedZ > angleSpeedZmax) angleSpeedZmax = angleSpeedZ;

        delay(50);
    }

    // TODO: Enhance this. This algorithm doesn't take into account
    // the fact that an extreme value couldn't be accurate.
    // Example: take the median.
    angleSpeedXoffset = (angleSpeedXmax + angleSpeedXmin) / 2;
    angleSpeedYoffset = (angleSpeedYmax + angleSpeedYmin) / 2;
    angleSpeedZoffset = (angleSpeedZmax + angleSpeedZmin) / 2;

    // sensor.magXOffset = -(MAG_X_MAX + MAG_X_MIN) / 2;
    // sensor.magYOffset = -(MAG_Y_MAX + MAG_Y_MIN) / 2;
}
