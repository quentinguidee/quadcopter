#include "pid.h"

#include "log.h"

PID::PID(float Kp, float Ki, float Kd, float min, float max) :
    Kp(Kp), Ki(Ki), Kd(Kd),
    minOutput(min), maxOutput(max),
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
    unsigned long deltaTime = (micros() - timer) * 0.001;
    float error = desired - measured;

    integral += error * deltaTime;
    derivative = (error - previousError) / deltaTime;

    setOutput((Kp * error) + (Ki * integral) + (Kd * derivative));

    previousError = error;
    timer = micros();
}

float PID::getOutput()
{
    return output;
}

void PID::setKp(float value)
{
    Kp = value;
    Log::info(String("PID"), String("Set Kp to ") + value);
}

void PID::setKi(float value)
{
    Ki = value;
    Log::info(String("PID"), String("Set Ki to ") + value);
}

void PID::setKd(float value)
{
    Kd = value;
    Log::info(String("PID"), String("Set Kd to ") + value);
}

void PID::setOutput(float output)
{
    if (output < minOutput)
    {
        this->output = minOutput;
    }
    else if (output > maxOutput)
    {
        this->output = maxOutput;
    }
    else
    {
        this->output = output;
    }
}
