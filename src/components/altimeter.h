#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "component.h"

class Altimeter : public Component
{
private:
    float z, previousZ;
    float rateZ;

    unsigned long timer;

public:
    Altimeter();
    ~Altimeter() {}

    void tick();

    float getZ() { return z; }
    float getRateZ() { return rateZ; }

    void forceSetZ(float z);
    void computeRateZ();
};

#endif /* ALTIMETER_H */
