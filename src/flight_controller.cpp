#include "flight_controller.h"

#include "interface/send.h"
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

    desiredX(0), desiredY(0), desiredZ(1.2), desiredR(0),

    flightModel(FlightModel::disabled)
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

Vector4<uint16_t> FlightController::tick(
    float angleX,
    float angleY,
    float angleZ,

    float angleRateX,
    float angleRateY,
    float angleRateZ,

    float altitude)
{
    if (flightModel == FlightModel::disabled)
    {
        return Vector4<uint16_t>(0, 0, 0, 0);
    }

    if (flightModel == FlightModel::normal)
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

        float altitudeRate = pidAltitude.getOutput();
        float angleRateX = pidAngleRateX.getOutput();
        float angleRateY = pidAngleRateY.getOutput();
        float angleRateZ = pidAngleRateZ.getOutput();

        float motorASpeed = 25 + altitudeRate /* + angleRateX - angleRateY + angleRateZ */;
        float motorBSpeed = 25 + altitudeRate /* - angleRateX - angleRateY - angleRateZ */;
        float motorCSpeed = 25 + altitudeRate /* + angleRateX + angleRateY - angleRateZ */;
        float motorDSpeed = 25 + altitudeRate /* - angleRateX + angleRateY + angleRateZ */;

        if (motorASpeed >= 50 || motorBSpeed >= 50 || motorCSpeed >= 50 || motorDSpeed >= 50)
        {
            emergencyStop();
            return Vector4<uint16_t>(0, 0, 0, 0);
        }

        return Vector4<uint16_t>(motorASpeed, motorBSpeed, motorCSpeed, motorDSpeed);
    }

    if (flightModel == FlightModel::motorsTest)
    {
        return Vector4<uint16_t>(25, 25, 25, 25);
    }
}

void FlightController::emergencyStop()
{
    flightModel = FlightModel::disabled;
}

void FlightController::liftoff()
{
    flightModel = FlightModel::normal;
}

void FlightController::landing()
{
    flightModel = FlightModel::disabled;
}

void FlightController::configureForMotorsTest()
{
    flightModel = FlightModel::motorsTest;
    Send::startTestMotors();
}

void FlightController::stopMotorsTest()
{
    flightModel = FlightModel::disabled;
    Send::stopTestMotors();
}
