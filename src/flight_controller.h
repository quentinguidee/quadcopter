#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include <Arduino.h>

#include "utils/pid.h"

class FlightController
{
private:
    PID pidAngleX, pidAngleY, pidAngleZ;
    PID pidAngleRateX, pidAngleRateY, pidAngleRateZ;

    PID pidAltitude;

    float desiredX, desiredY, desiredZ, desiredR;

public:
    FlightController();
    ~FlightController() {}

    void startup();
    void tick(
        float angleX,
        float angleY,
        float angleZ,

        float angleRateX,
        float angleRateY,
        float angleRateZ,

        float altitude);

    void setDesiredX(float value) { desiredX = value; }
    void setDesiredY(float value) { desiredY = value; }
    void setDesiredZ(float value) { desiredZ = value; }
    void setDesiredR(float value) { desiredR = value; }

    PID& getPIDAngleX() { return pidAngleX; }
    PID& getPIDAngleY() { return pidAngleY; }
    PID& getPIDAngleZ() { return pidAngleZ; }

    PID& getPIDAngleRateX() { return pidAngleRateX; }
    PID& getPIDAngleRateY() { return pidAngleRateY; }
    PID& getPIDAngleRateZ() { return pidAngleRateZ; }

    PID& getPIDAltitude() { return pidAltitude; }
};

#endif /* FLIGHT_CONTROLLER_H */
