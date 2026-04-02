#include "error.h"

namespace Error {
    void raiseError(const char* file, const char* function, const char* note)
    {
        Serial.println();

        Serial.print(F("[ERROR] "));
        Serial.println(file);
        Serial.print(F("   > "));
        Serial.print(function);
        Serial.print(F(" > "));
        Serial.println(note);

        while(1);
    }

    void raiseWarning(const char* file, const char* function, const char* note)
    {
        Serial.println();

        Serial.print(F("[WARNING] "));
        Serial.println(file);
        Serial.print(F("   > "));
        Serial.print(function);
        Serial.print(F(" > "));
        Serial.println(note);

        while(1);
    }
}