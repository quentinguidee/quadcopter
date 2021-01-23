#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include <Arduino.h>

#include "utils/pid.h"

class FlightController
{
private:
    PID pidAngleX, pidAngleY;
    PID pidAngleRateX, pidAngleRateY;

public:
    FlightController();
    ~FlightController() {}

    void startup();
    void tick(
        float angleX,
        float angleY,
        float angleRateX,
        float angleRateY);
};

#endif /* FLIGHT_CONTROLLER_H */
