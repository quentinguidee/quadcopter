#include "flight_controller.h"

#include "utils/log.h"

// TODO: Tune values
FlightController::FlightController() :
    pidAngleX(PID(1, 0, 0, -90, 90)),
    pidAngleY(PID(1, 0, 0, -90, 90)),
    pidAngleZ(PID(1, 0, 0, -90, 90)),

    pidAngleRateX(PID(1, 0, 0, -180, 180)),
    pidAngleRateY(PID(1, 0, 0, -180, 180)),
    pidAngleRateZ(PID(1, 0, 0, -180, 180)),

    pidAltitude(PID(3, 0.3, 12, -50, 50)),

    desiredX(0), desiredY(0), desiredZ(1.2), desiredR(0)
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

    pidAltitude.startup();

    desiredX = 0;
    desiredY = 0;
    desiredZ = 1.2;
    desiredR = 0;
}

void FlightController::tick(
    float angleX,
    float angleY,
    float angleZ,

    float angleRateX,
    float angleRateY,
    float angleRateZ,

    float altitude)
{
    // Log::info(String("FLIGHT_CONTROLLER"), String("Will try to reach: ") + desiredX + "/" + desiredY + "/" + desiredZ + "/" + desiredR);

    pidAngleX.tick(0, angleX);
    pidAngleY.tick(0, angleY);
    pidAngleZ.tick(0, angleZ);
    // Log::info(String("FLIGHT_CONTROLLER"), String("PID RAW: ") + pidAngleX.getOutput() + "/" + pidAngleY.getOutput() + "/" + pidAngleZ.getOutput());

    pidAngleRateX.tick(pidAngleX.getOutput(), angleRateX);
    pidAngleRateY.tick(pidAngleY.getOutput(), angleRateY);
    pidAngleRateZ.tick(pidAngleZ.getOutput(), angleRateZ);

    pidAltitude.tick(desiredZ, altitude);
    // Log::info(String("FLIGHT_CONTROLLER"), String("PID RATES: ") + pidAltitude.getOutput() + "/" + pidAngleRateX.getOutput() + "/" + pidAngleRateY.getOutput() + "/" + pidAngleRateZ.getOutput());
}
