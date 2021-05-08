#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

namespace Log {

void log(String type, String tag, String s);

void info(String tag, String s);
void warning(String tag, String s);
void error(String tag, String s);

};  // namespace Log

#endif /* LOG_H */
