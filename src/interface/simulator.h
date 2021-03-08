#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <Arduino.h>

class Simulator
{
private:
public:
    Simulator() {}
    ~Simulator() {}

    static void send(String message);

    static void callbackSimModeEnabled();
};

#endif /* SIMULATOR_H */
