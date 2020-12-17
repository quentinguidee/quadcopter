#include "static_fire_test.h"

#include "../interface/interface.h"

StaticFireTest::StaticFireTest() :
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
    String command = String("M1") + currentMotor;
    Interface::execute(command);
    Serial.print("[TEST] Execute ");
    Serial.println(command);
    currentState = State::running;
}

void StaticFireTest::shutdown(int8_t currentMotor)
{
    String command = String("M0") + currentMotor;
    Interface::execute(command);
    Serial.print("[TEST] Execute ");
    Serial.println(command);
    currentState = State::stopped;
}
