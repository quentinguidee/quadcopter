#include "position.h"

#include "interface/send.h"

Position::Position(Accelerometer& accelerometer, Altimeter& altimeter) :
    accelerometer(accelerometer),
    altimeter(altimeter),

    angleX(0),
    angleY(0),
    angleZ(0),
    x(0), y(0), z(0),
    timer(0)
{
}

void Position::update()
{
    unsigned long now = micros();
    if (timer != 0)
    {
        float deltaTime = (now - timer) / 1000000.0;
        angleX = 0.995 * (angleX + (accelerometer.getAngleSpeedX() * deltaTime)) + (0.005 * accelerometer.getAccelerationAngleX());
        angleY = 0.995 * (angleY + (accelerometer.getAngleSpeedY() * deltaTime)) + (0.005 * accelerometer.getAccelerationAngleY());
        angleZ += accelerometer.getAngleSpeedZ() * deltaTime;

        z = altimeter.getZ();
    }
    timer = now;

    Send::positionTelemetry(getX(), getY(), getZ());
    Send::angleTelemetry(getAngleX(), getAngleY(), getAngleZ());
}
