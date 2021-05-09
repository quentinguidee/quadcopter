#include "toggle_button.h"

#include "../utils/log.h"

ToggleButton::ToggleButton(uint8_t pin) :
    pin(pin),
    previous(LOW),
    timer(Timer()),
    state(false),
    hasChanged(false)
{
}

void ToggleButton::startup()
{
    pinMode(pin, INPUT);
    timer.reset();
    Log::info("TOGGLE_BUTTON", "Startup");
}

void ToggleButton::tick()
{
    hasChanged = false;
    int now = digitalRead(pin);
    if (now == HIGH && previous == LOW && timer.exceeded(DELAY))
    {
        hasChanged = true;
        state = !state;
        timer.reset();
        Log::info("TOGGLE_BUTTON", "State changed to " + String(state));
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

void ToggleButton::on()
{
    state = true;
    hasChanged = true;
}

void ToggleButton::off()
{
    state = false;
    hasChanged = true;
}

bool ToggleButton::getHasChanged()
{
    return hasChanged;
}
