#include "position.h"

Position::Position(Accelerometer& sensor) :
    sensor(sensor),
    angleX(0),
    angleY(0),
    angleZ(0),
    timer(0)
{
}

void Position::update()
{
    unsigned long now = micros();
    if (timer != 0)
    {
        float deltaTime = (now - timer) / 1000000.0;
        angleX += sensor.getAngleSpeedX() * deltaTime;
        angleY += sensor.getAngleSpeedY() * deltaTime;
        angleZ += sensor.getAngleSpeedZ() * deltaTime;
    }
    timer = now;
}
