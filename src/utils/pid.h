#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID
{
private:
    float Kp, Ki, Kd;

    float previousError;
    float integral;
    float derivative;

    float output;

    unsigned long timer;

public:
    PID(float Kp, float Ki, float Kd);
    ~PID() {}

    void tick(float desired, float measured);

    float getOutput();
};

#endif /* PID_H */
