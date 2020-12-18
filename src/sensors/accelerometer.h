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

    float angleXoffset;
    float angleYoffset;
    float angleZoffset;

    float magneticFieldX;
    float magneticFieldY;
    float magneticFieldZ;
    float horizonDirection;

public:
    Accelerometer() {}
    ~Accelerometer() {}

    void setup();
    void tick();

    void updateAccelerations();
    void updateAngles();
    void updateMagneticFields();

    void calibrate();

    float getAccelerationX() { return accelerationX; }
    float getAccelerationY() { return accelerationY; }
    float getAccelerationZ() { return accelerationZ; }
    float getAcceleration() { return acceleration; }

    float getAngleX() { return angleX - angleXoffset; }
    float getAngleY() { return angleY - angleYoffset; }
    float getAngleZ() { return angleZ - angleZoffset; }

    float getMagneticFieldX() { return magneticFieldX; }
    float getMagneticFieldY() { return magneticFieldY; }
    float getMagneticFieldZ() { return magneticFieldZ; }
    float getHorizonDirection() { return horizonDirection; }
};

#endif /* ACCELEROMETER_H */
