#include "log.h"

void Log::log(String type, String tag, String s)
{
    Serial.println((String) "[" + type + "|" + tag + "] " + s);
}

void Log::info(String tag, String s)
{
    Log::log("INFO", tag, s);
}

void Log::warning(String tag, String s)
{
    Log::log("WARNING", tag, s);
}

void Log::error(String tag, String s)
{
    Log::log("ERROR", tag, s);
}
