#include "pid.h"

PID::PID(float Kp, float Ki, float Kd) :
    Kp(Kp), Ki(Ki), Kd(Kd),
    previousError(0),
    integral(0),
    derivative(0),
    output(0),
    timer(millis())
{
}

void PID::startup()
{
    previousError = 0;
    integral = 0;
    derivative = 0;
    output = 0;
    timer = millis();
}

void PID::tick(float desired, float measured)
{
    unsigned long deltaTime = micros() - timer;
    float error = desired - measured;

    integral += error * deltaTime;
    derivative = (error - previousError) / deltaTime;

    output = (Kp * error) + (Ki * integral) + (Kd * derivative);

    previousError = error;
    timer = micros();
}

float PID::getOutput()
{
    return output;
}
