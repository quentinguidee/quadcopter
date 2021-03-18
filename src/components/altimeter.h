#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "component.h"

class Altimeter : public Component
{
private:
    float z;
    float rateZ;

    unsigned long timer;

public:
    Altimeter();
    ~Altimeter() {}

    void tick();

    float getZ() { return z; }
    float getRateZ() { return rateZ; }

    void forceSetZ(float z);
};

#endif /* ALTIMETER_H */
