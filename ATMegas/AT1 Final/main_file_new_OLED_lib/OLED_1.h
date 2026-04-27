#ifndef OLED_1_H
#define OLED_1_H
#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include <U8g2lib.h>  // replaces Adafruit headers

namespace OLED1
{
    constexpr int     SCREEN_WIDTH   = 128;
    constexpr int     SCREEN_HEIGHT  = 64;
    constexpr uint8_t SCREEN_ADDRESS = 0x3C; // still valid, U8g2 auto-detects on HW_I2C

    bool begin();
    void printCenteredString(const char* str);
    bool isReady();
    void clear();
}
#endif