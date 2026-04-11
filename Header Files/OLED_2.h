#ifndef OLED_2_H
#define OLED_2_H

#include <Arduino.h>
#include <stdint.h>

namespace OLED2 
{
	constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 64;
    constexpr uint8_t SCREEN_ADDRESS = 0x3D;

    bool begin();
    void showVolumeLevel(int rectX, int rectWidth, int vol);
    bool isReady();
}

#endif