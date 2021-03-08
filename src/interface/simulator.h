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

    static void setLed(uint8_t pin, bool on);
    static void enableLed(uint8_t pin);
    static void disableLed(uint8_t pin);
};

#endif /* SIMULATOR_H */
