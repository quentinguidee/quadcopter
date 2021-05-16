#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU9250_asukiaaa.h>

#include "component.h"

class Accelerometer : public Component
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

    float angleXFromAcceleration;
    float angleYFromAcceleration;

    float magneticFieldX;
    float magneticFieldY;
    float magneticFieldZ;
    float horizonDirection;

public:
    Accelerometer() {}
    ~Accelerometer() {}

    void startup();
    void tick();

    void updateAccelerations();
    void updateAngles();
    void updateAnglesFromAccelerations();
    void updateMagneticFields();

    void calibrate();

    float getAccelerationX() { return accelerationX - accelerationXoffset; }
    float getAccelerationY() { return accelerationY - accelerationYoffset; }
    float getAccelerationZ() { return accelerationZ - accelerationZoffset; }
    float getAcceleration() { return acceleration; }

    float getAngleSpeedX() { return angleSpeedX - angleSpeedXoffset; }
    float getAngleSpeedY() { return angleSpeedY - angleSpeedYoffset; }
    float getAngleSpeedZ() { return angleSpeedZ - angleSpeedZoffset; }

    float getAccelerationAngleX() { return angleXFromAcceleration; }
    float getAccelerationAngleY() { return angleYFromAcceleration; }

    float getMagneticFieldX() { return magneticFieldX; }
    float getMagneticFieldY() { return magneticFieldY; }
    float getMagneticFieldZ() { return magneticFieldZ; }
    float getHorizonDirection() { return horizonDirection; }

    void forceSetAccelerationX(float accelerationX) { this->accelerationX = accelerationX; }
    void forceSetAccelerationY(float accelerationY) { this->accelerationY = accelerationY; }
    void forceSetAccelerationZ(float accelerationZ) { this->accelerationZ = accelerationZ; }

    void forceSetAngleSpeedX(float angleSpeedX) { this->angleSpeedX = angleSpeedX; }
    void forceSetAngleSpeedY(float angleSpeedY) { this->angleSpeedY = angleSpeedY; }
    void forceSetAngleSpeedZ(float angleSpeedZ) { this->angleSpeedZ = angleSpeedZ; }
};

#endif /* ACCELEROMETER_H */
