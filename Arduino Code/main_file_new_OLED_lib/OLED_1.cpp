#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "OLED_1.h"
#include "error.h"

namespace OLED1
{
    static constexpr int LETTER_WIDTH  = 5;
    static constexpr int LETTER_HEIGHT = 7;
    static constexpr int MAX_FONT_SIZE = 4; // U8g2 uses named fonts, not integer sizes

    // _1 suffix = 128-byte page buffer (vs 1024 for Adafruit). Use _2 for 256 bytes if flicker is bad.
    U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

    bool configured = false;

    bool begin()
    {
        if (configured) return true;

        if (!display.begin())
            Serial.println(F("OLED 1 error"));
            // Error::raiseError(F(__FILE__), NULL, F("OLED 1 allocation failed"));

        display.clear();
        configured = true;
        return true;
    }

    bool isReady() { return configured; }

    void printCenteredString(const char* str)
    {
        if (!configured)
            Error::raiseError(F(__FILE__), NULL, F("OLED not configured"));

        int len = strlen(str);
        if (len < 1 || len > 20)
            Error::raiseError(F(__FILE__), NULL, F("Bad string length"));

        // Choose font based on string length (replaces your textSize logic)
        const uint8_t* font;
        if      (len <= 4)  font = u8g2_font_inb42_mr;
        else if (len <= 6)  font = u8g2_font_logisoso16_tr;
        else if (len <= 12) font = u8g2_font_t0_11_tr;        // clean, compact, confirmed valid
        else                font = u8g2_font_6x10_tr;

        display.setFont(font);
        int strWidth  = display.getStrWidth(str);
        int strHeight = display.getAscent() - display.getDescent();

        int xPos = (SCREEN_WIDTH  - strWidth)  / 2;
        int yPos = (SCREEN_HEIGHT + strHeight) / 2 - 10; // U8g2 y is baseline

        // Page-buffer mode requires this loop instead of a single display()
        display.firstPage();
        do {
            display.drawStr(xPos, yPos, str);
        } while (display.nextPage());
    }

    void clear()
    {
        display.clear();
    }
}