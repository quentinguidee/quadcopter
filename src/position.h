#ifndef POSITION_H
#define POSITION_H

#include "components/accelerometer.h"

class Position
{
private:
    Accelerometer& sensor;

    float x, y, z;
    float angleX, angleY, angleZ;

    unsigned long timer;

public:
    Position(Accelerometer& sensor);
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
