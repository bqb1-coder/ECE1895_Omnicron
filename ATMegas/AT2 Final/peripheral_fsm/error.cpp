#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "error.h"

namespace Error {
    void raiseError(const __FlashStringHelper* file, const char* function, const __FlashStringHelper* note)
    {
        Serial.println();

        Serial.print(F("[ERROR] "));
        Serial.println(file);
        if (function) {
            Serial.print(F("   > "));
            Serial.print(function);
        }
        Serial.print(F(" > "));
        Serial.println(note);

        while(1);
    }

    void raiseWarning(const __FlashStringHelper* file, const char* function, const __FlashStringHelper* note)
    {
        Serial.println();

        Serial.print(F("[WARNING] "));
        Serial.println(file);
        if (function) {
            Serial.print(F("   > "));
            Serial.print(function);
        }
        Serial.print(F(" > "));
        Serial.println(note);
    }
}