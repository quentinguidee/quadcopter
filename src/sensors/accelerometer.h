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

    float accelerationXoffset;
    float accelerationYoffset;
    float accelerationZoffset;

    float angleSpeedX;
    float angleSpeedY;
    float angleSpeedZ;

    float angleSpeedXoffset;
    float angleSpeedYoffset;
    float angleSpeedZoffset;

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

    float getAccelerationX() { return accelerationX - accelerationXoffset; }
    float getAccelerationY() { return accelerationY - accelerationYoffset; }
    float getAccelerationZ() { return accelerationZ - accelerationZoffset; }
    float getAcceleration() { return acceleration; }

    float getAngleSpeedX() { return angleSpeedX - angleSpeedXoffset; }
    float getAngleSpeedY() { return angleSpeedY - angleSpeedYoffset; }
    float getAngleSpeedZ() { return angleSpeedZ - angleSpeedZoffset; }

    float getMagneticFieldX() { return magneticFieldX; }
    float getMagneticFieldY() { return magneticFieldY; }
    float getMagneticFieldZ() { return magneticFieldZ; }
    float getHorizonDirection() { return horizonDirection; }
};

#endif /* ACCELEROMETER_H */
