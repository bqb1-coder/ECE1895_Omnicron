#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>
#include <stdint.h>

namespace Error {
    void raiseError(const __FlashStringHelper* file,
                    const char* func,
                    const __FlashStringHelper* note);
    void raiseWarning(const __FlashStringHelper* file,
                      const char* func,
                      const __FlashStringHelper* note);
}

#endif