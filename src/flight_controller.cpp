#include "flight_controller.h"

// TODO: Tune values
FlightController::FlightController() :
    pidAngleX(PID(1, 1, 1)),
    pidAngleY(PID(1, 1, 1)),

    pidAngleRateX(PID(1, 1, 1)),
    pidAngleRateY(PID(1, 1, 1))
{
}

void FlightController::startup()
{
    pidAngleX.startup();
    pidAngleY.startup();

    pidAngleRateX.startup();
    pidAngleRateY.startup();
}

void FlightController::tick(
    float angleX,
    float angleY,
    float angleRateX,
    float angleRateY)
{
    pidAngleX.tick(0, angleX);
    pidAngleY.tick(0, angleY);

    pidAngleRateX.tick(pidAngleX.getOutput(), angleRateX);
    pidAngleRateY.tick(pidAngleY.getOutput(), angleRateY);
}
