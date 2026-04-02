#ifndef OLED_1_H
// #ifdef INCLUDE_OLED_1
#define OLED_1_H

#include <Arduino.h>
#include <stdint.h>
#include <string.h>

namespace OLED1
{
    constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 64;
    constexpr uint8_t SCREEN_ADDRESS = 0x3C;

    bool begin();
    void printCenteredString(const char* str);
    bool isReady();
}

// #endif
#endif