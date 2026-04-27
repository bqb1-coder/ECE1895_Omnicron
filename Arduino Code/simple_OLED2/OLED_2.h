#ifndef OLED_2_H
#define OLED_2_H

#include <Arduino.h>
#include <stdint.h>
#include <Adafruit_SSD1306.h>



namespace OLED2 
{
    #define WHITE 1
	constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 64;
    constexpr uint8_t SCREEN_ADDRESS = 0x3C;

    bool begin();
    void showVolumeLevel(int vol, int color=WHITE);
    void clearVolumeLevel(int vol);
    void drawTargetBox(int rectX, int rectWidth);
    bool isReady();
    void clearDisplay();
}

#endif