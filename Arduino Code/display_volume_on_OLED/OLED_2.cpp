#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include "OLED_2.h"
#include "Error.h"

namespace OLED2
{
	static constexpr int CIRCLE_Y = 40;
	static constexpr int CIRCLE_R = 5;
	static constexpr int RECTANGLE_Y = 56;
	static constexpr int RECTANGLE_H = 8;

	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    bool configured = false;

    bool begin()
    {
        if (configured)
            return true;

        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
            Error::raiseError(__FILE__, __func__, "SSD1306 allocation failed");

        display.setTextColor(WHITE);
        display.clearDisplay();
        display.display();

        configured = true;
        return true;
    }

    bool isReady()
    {
        return configured;
    }

    void showVolumeLevel(int rectX, int rectWidth, int vol)
    {
    	display.clearDisplay();
		display.fillCircle(vol, CIRCLE_Y, CIRCLE_R, WHITE);
		display.fillRect(rectX, RECTANGLE_Y, rectWidth, RECTANGLE_H, WHITE);
		display.display();
    }
}