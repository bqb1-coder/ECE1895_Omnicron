#ifndef OLED_1_H
#ifdef INCLUDE_OLED_1
#define OLED_1_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace OLED1
{
    constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 64;
    constexpr uint8_t SCREEN_ADDRESS = 0x3C;

    bool begin();
    void printCentered(const char* str);
    bool isReady();
}

#endif
#endif