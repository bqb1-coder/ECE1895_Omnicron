#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "OLED_1.h"
#include "error.h"


namespace OLED1
{
    static constexpr int LETTER_WIDTH = 5;
    static constexpr int LETTER_HEIGHT = 7;
    static constexpr int MAX_FONT_SIZE = 6;

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    bool configured = false;

    bool begin()
    {
        if (configured)
            return true;

        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
            Error::raiseError(__FILE__, __func__, "OLED 1 allocation failed");

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

    void printCenteredString(const char* str)
    {
        if (!configured)
            Error::raiseError(__FILE__, __func__, "OLED not configured");


        int len = strlen(str);
        if (len < 1 || len > 20)
            Error::raiseError(__FILE__, __func__, "Bad string length");
        

        int horzPixelsNeeded = SCREEN_WIDTH / (len * (LETTER_WIDTH + 1));

        int textSize = min(horzPixelsNeeded, MAX_FONT_SIZE);

        int xPos = SCREEN_WIDTH / 2 - (LETTER_WIDTH + 1) * len * textSize / 2;

        int yPos = SCREEN_HEIGHT / 2 - (LETTER_HEIGHT + 1) * textSize / 2;

        display.clearDisplay();
        display.setTextSize(textSize);
        display.setCursor(xPos, yPos);
        display.print(str);
        display.display();
    }
}