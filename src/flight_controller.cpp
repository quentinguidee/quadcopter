#include "flight_controller.h"

#include "utils/log.h"

// TODO: Tune values
FlightController::FlightController() :
    pidAngleX(PID(1, 0, 0, -90, 90)),
    pidAngleY(PID(1, 0, 0, -90, 90)),
    pidAngleZ(PID(1, 0, 0, -90, 90)),
    pidAltitude(PID(1, 0, 0, -100, 100)),

    pidAngleRateX(PID(1, 0, 0, -180, 180)),
    pidAngleRateY(PID(1, 0, 0, -180, 180)),
    pidAngleRateZ(PID(1, 0, 0, -180, 180)),
    pidAltitudeRate(PID(10, 0.01, 10, 0, 180))
{
}

void FlightController::startup()
{
    pidAngleX.startup();
    pidAngleY.startup();
    pidAngleZ.startup();
    pidAltitude.startup();

    pidAngleRateX.startup();
    pidAngleRateY.startup();
    pidAngleRateZ.startup();
    pidAltitudeRate.startup();
}

void FlightController::tick(
    float angleX,
    float angleY,
    float angleZ,
    float altitude,

    float angleRateX,
    float angleRateY,
    float angleRateZ,
    float altitudeRate)
{
    pidAngleX.tick(0, angleX);
    pidAngleY.tick(0, angleY);
    pidAngleZ.tick(0, angleZ);
    pidAltitude.tick(1, altitude);
    Log::info(String("FLIGHT_CONTROLLER"), String("PID RAW: ") + pidAltitude.getOutput() + "/" + pidAngleX.getOutput() + "/" + pidAngleY.getOutput() + "/" + pidAngleZ.getOutput());

    pidAngleRateX.tick(pidAngleX.getOutput(), angleRateX);
    pidAngleRateY.tick(pidAngleY.getOutput(), angleRateY);
    pidAngleRateZ.tick(pidAngleZ.getOutput(), angleRateZ);
    pidAltitudeRate.tick(pidAltitude.getOutput(), altitudeRate);
    Log::info(String("FLIGHT_CONTROLLER"), String("PID RATES: ") + pidAltitudeRate.getOutput() + "/" + pidAngleRateX.getOutput() + "/" + pidAngleRateY.getOutput() + "/" + pidAngleRateZ.getOutput());
}
