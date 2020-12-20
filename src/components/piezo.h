#ifndef PIEZO_H
#define PIEZO_H

#include <Arduino.h>

class Piezo
{
private:
    uint8_t pin;

    unsigned long currentTimer;
    unsigned long startTimer;
    unsigned long duration = 0;

    int pause = 0;

    int *frequencies;
    int frequencyIndex;
    uint8_t frequenciesCount;

public:
    Piezo(uint8_t pin);
    ~Piezo() {}

    void startup();
    void shutdown();
    void tick();

    void on(int frequencies[], int duration, uint8_t count, bool force = false);

    bool isOn();
};

#endif /* PIEZO_H */
