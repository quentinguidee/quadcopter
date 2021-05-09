#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H

#include <Arduino.h>

#include "../utils/timer.h"

class ToggleButton
{
private:
    uint8_t pin;
    int previous;
    bool state;
    bool hasChanged;

    Timer timer;
    const int DELAY = 200;

public:
    ToggleButton(uint8_t pin);
    ~ToggleButton() {}

    void startup();
    void tick();

    bool isOn();
    bool isOff();
    void on();
    void off();
    bool getHasChanged();
};

#endif /* TOGGLE_BUTTON_H */
