#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include <Arduino.h>

#include "utils/pid.h"

class FlightController
{
private:
    PID pidAngleX, pidAngleY, pidAngleZ;
    PID pidAngleRateX, pidAngleRateY, pidAngleRateZ;

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
        float angleRateZ);
};

#endif /* FLIGHT_CONTROLLER_H */
