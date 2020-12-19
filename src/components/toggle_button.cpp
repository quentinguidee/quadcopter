#include "toggle_button.h"

ToggleButton::ToggleButton(uint8_t pin) :
    pin(pin),
    previous(LOW),
    timer(0),
    state(false),
    hasChanged(false)
{
}

void ToggleButton::setup()
{
    pinMode(pin, INPUT);
}

void ToggleButton::tick()
{
    hasChanged = false;
    int now = digitalRead(pin);
    if (now == HIGH && previous == LOW && millis() - timer > delay)
    {
        hasChanged = true;
        state = !state;
        timer = millis();
    }
    previous = now;
}

bool ToggleButton::isOn()
{
    return state;
}

bool ToggleButton::isOff()
{
    return !state;
}

bool ToggleButton::getHasChanged()
{
    return hasChanged;
}
