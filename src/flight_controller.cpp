#include "flight_controller.h"

// TODO: Tune values
FlightController::FlightController() :
    pidAngleX(PID(1, 1, 1)),
    pidAngleY(PID(1, 1, 1)),
    pidAngleZ(PID(1, 1, 1)),

    pidAngleRateX(PID(1, 1, 1)),
    pidAngleRateY(PID(1, 1, 1)),
    pidAngleRateZ(PID(1, 1, 1))
{
}

void FlightController::startup()
{
    pidAngleX.startup();
    pidAngleY.startup();
    pidAngleZ.startup();

    pidAngleRateX.startup();
    pidAngleRateY.startup();
    pidAngleRateZ.startup();
}

void FlightController::tick(
    float angleX,
    float angleY,
    float angleZ,
    float angleRateX,
    float angleRateY,
    float angleRateZ)
{
    pidAngleX.tick(0, angleX);
    pidAngleY.tick(0, angleY);
    pidAngleZ.tick(0, angleZ);

    pidAngleRateX.tick(pidAngleX.getOutput(), angleRateX);
    pidAngleRateY.tick(pidAngleY.getOutput(), angleRateY);
    pidAngleRateZ.tick(pidAngleZ.getOutput(), angleRateZ);
}
