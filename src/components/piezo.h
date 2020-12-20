#ifndef PIEZO_H
#define PIEZO_H

#include <Arduino.h>

class Piezo
{
private:
    uint8_t pin;

    unsigned long currentTimer;
    unsigned long startTimer;
    unsigned long period;

    int repeat;
    int pause = 0;

    int frequency = 440;

    bool inStartup = false;

public:
    Piezo(uint8_t pin);
    ~Piezo() {}

    void startup();
    void shutdown();
    void tick();

    void on(int frequency, int duration, int repeat = 1);
};

#endif /* PIEZO_H */
