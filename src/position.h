#ifndef POSITION_H
#define POSITION_H

#include "components/accelerometer.h"
#include "components/altimeter.h"

class Position
{
private:
    Accelerometer& accelerometer;
    Altimeter& altimeter;

    float x, y, z;
    float angleX, angleY, angleZ;

    unsigned long timer;

public:
    Position(Accelerometer& accelerometer, Altimeter& altimeter);
    ~Position() {}

    void update();

    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }

    float getAngleX() { return angleX; }
    float getAngleY() { return angleY; }
    float getAngleZ() { return angleZ; }
};

#endif /* POSITION_H */
