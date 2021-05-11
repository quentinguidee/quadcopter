#ifndef SEND_H
#define SEND_H

#include <Arduino.h>

namespace Send {

void message(String message);

void shutdownDone();
void startupDone();

void ledEnabled(uint8_t pin);
void ledDisabled(uint8_t pin);

};  // namespace Send

#endif /* SEND_H */
