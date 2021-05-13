#ifndef SEND_H
#define SEND_H

#include <Arduino.h>

namespace Send {

void message(String message);

void shutdownDone();
void startupDone();

void ledEnabled(uint8_t pin);
void ledDisabled(uint8_t pin);

void motorStartup(uint8_t id);
void motorShutdown(uint8_t id);
void motorSpeedChanged(uint8_t id, uint16_t speed);

void accelerometerStartup();
void accelerometerCalibrated();

void positionTelemetry(float x, float y, float z);
void angleTelemetry(float x, float y, float z);

};  // namespace Send

#endif /* SEND_H */
