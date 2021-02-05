#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

class Log
{
private:
public:
    Log() {}
    ~Log() {}

    static void info(String tag, String s);
    static void warning(String tag, String s);
    static void error(String tag, String s);
};

#endif /* LOG_H */
