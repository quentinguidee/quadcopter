#include "log.h"

void Log::info(String tag, String s)
{
    Serial.print("[INFO|");
    Serial.print(tag);
    Serial.print("] ");
    Serial.println(s);
}

void Log::warning(String tag, String s)
{
    Serial.print("[WARNING|");
    Serial.print(tag);
    Serial.print("] ");
    Serial.println(s);
}

void Log::error(String tag, String s)
{
    Serial.print("[ERROR|");
    Serial.print(tag);
    Serial.print("] ");
    Serial.println(s);
}
