#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID
{
private:
    float Kp, Ki, Kd;
    float minOutput, maxOutput;

    float previousError;
    float integral;
    float derivative;

    float output;

    unsigned long timer;

    void setOutput(float output);

public:
    PID(float Kp, float Ki, float Kd, float min, float max);
    ~PID() {}

    void startup();
    void tick(float desired, float measured);

    float getOutput();

    void setKp(float value);
    void setKi(float value);
    void setKd(float value);
};

#endif /* PID_H */
