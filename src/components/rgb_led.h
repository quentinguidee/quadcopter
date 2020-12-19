#ifndef RGB_LED_H
#define RGB_LED_H

#include <Arduino.h>

class RGBLed
{
private:
    uint8_t greenPin, redPin, bluePin;
    uint8_t green, red, blue;

public:
    RGBLed(uint8_t greenPin, uint8_t redPin, uint8_t bluePin);
    ~RGBLed() {}

    void setup();

    void on();
    void off();

    void refresh();
    void setColor(uint8_t red, uint8_t green, uint8_t blue, bool refresh = true);
};

#endif /* RGB_LED_H */
