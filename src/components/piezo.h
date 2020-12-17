#ifndef PIEZO_H
#define PIEZO_H

#include <Arduino.h>

class Piezo
{
private:
    uint8_t pin;

public:
    Piezo(uint8_t pin);
    ~Piezo() {}
};

#endif /* PIEZO_H */
