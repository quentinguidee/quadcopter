#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H

#include <Arduino.h>

class ToggleButton
{
private:
    uint8_t pin;
    int previous;
    bool state;
    bool hasChanged;

    unsigned long timer;
    const int delay = 200;

public:
    ToggleButton(uint8_t pin);
    ~ToggleButton() {}

    void setup();
    void tick();

    bool isOn();
    bool isOff();
    bool getHasChanged();
};

#endif /* TOGGLE_BUTTON_H */
