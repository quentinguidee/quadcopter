#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include <Arduino.h>

#include "utils/pid.h"

class FlightController
{
private:
    PID pidAngleX, pidAngleY, pidAngleZ, pidAltitude;
    PID pidAngleRateX, pidAngleRateY, pidAngleRateZ, pidAltitudeRate;

public:
    FlightController();
    ~FlightController() {}

    void startup();
    void tick(
        float angleX,
        float angleY,
        float angleZ,
        float altitude,

        float angleRateX,
        float angleRateY,
        float angleRateZ,
        float altitudeRate);

    PID& getPIDAngleX() { return pidAngleX; }
    PID& getPIDAngleY() { return pidAngleY; }
    PID& getPIDAngleZ() { return pidAngleZ; }
    PID& getPIDAltitude() { return pidAltitude; }

    PID& getPIDAngleRateX() { return pidAngleRateX; }
    PID& getPIDAngleRateY() { return pidAngleRateY; }
    PID& getPIDAngleRateZ() { return pidAngleRateZ; }
    PID& getPIDAltitudeRate() { return pidAltitudeRate; }
};

#endif /* FLIGHT_CONTROLLER_H */
