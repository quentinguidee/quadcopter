#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU9250_asukiaaa.h>

class Accelerometer
{
private:
    MPU9250_asukiaaa sensor;

    float accelerationX;
    float accelerationY;
    float accelerationZ;
    float acceleration;

    float angleX;
    float angleY;
    float angleZ;

    float magneticFieldX;
    float magneticFieldY;
    float magneticFieldZ;
    float horizonDirection;

public:
    Accelerometer() {}
    ~Accelerometer() {}

    void setup();
    void tick();

    float getAccelerationX() { return accelerationX; }
    float getAccelerationY() { return accelerationY; }
    float getAccelerationZ() { return accelerationZ; }
    float getAcceleration() { return acceleration; }

    float getAngleX() { return angleX; }
    float getAngleY() { return angleY; }
    float getAngleZ() { return angleZ; }

    float getMagneticFieldX() { return magneticFieldX; }
    float getMagneticFieldY() { return magneticFieldY; }
    float getMagneticFieldZ() { return magneticFieldZ; }
    float getHorizonDirection() { return horizonDirection; }
};

#endif /* ACCELEROMETER_H */
