#include "static_fire_test.h"

StaticFireTest::StaticFireTest(Drone &drone) :
    drone(drone),
    currentTimer(0),
    startTimer(0),
    period(3000),
    currentMotor(0),
    currentState(State::stopped)
{
}

void StaticFireTest::tick()
{
    if (currentMotor >= MOTORS_COUNT)
        return;

    currentTimer = millis();
    if (currentTimer - startTimer >= period)
    {
        switch (currentState)
        {
            case State::stopped:
                startup(currentMotor);
                period = 5000;
                startTimer = currentTimer;
                break;

            case State::running:
                shutdown(currentMotor);
                period = 3000;
                currentMotor++;
                startTimer = currentTimer;
                break;

            default: break;
        }
    }
}

void StaticFireTest::startup(int8_t currentMotor)
{
    drone.getMotor(currentMotor).startup();
    currentState = State::running;
}

void StaticFireTest::shutdown(int8_t currentMotor)
{
    drone.getMotor(currentMotor).shutdown();
    currentState = State::stopped;
}
