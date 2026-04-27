#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>
#include <stdint.h>

namespace Error {
    void raiseError(const char* file, const char* function, const char* note);
    void raiseWarning(const char* file, const char* function, const char* note);
}

#endif