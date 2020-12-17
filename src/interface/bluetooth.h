#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

class Bluetooth
{
private:
public:
    Bluetooth() {}
    ~Bluetooth() {}

    void setup();
    void tick();
};

#endif /* BLUETOOTH_H */
