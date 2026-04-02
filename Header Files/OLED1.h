#ifndef OLED_1_H
#ifdef INCLUDE_OLED_1

#define OLED_1_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_1_ADDRESS 0x3C
// #define SCREEN_2_ADDRESS 0x3D
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 7

Adafruit_SSD1306 keypadDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool OLED__configured = false;

bool beginDisplay(int SCREEN_ADDRESS) {
  delay(500);
  
  if(!keypadDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    ERR__raiseError(__FILE__, __func__, "SSD1306 Allocation failed");
  }

  keypadDisplay.setTextColor(WHITE);
  keypadDisplay.clearDisplay();
  keypadDisplay.display();

  OLED__configured = true;
  return OLED__configured;
}


void printCenteredString(char * str, int len)
{
  
  if (!OLED__configured)
    ERR__raiseError(__FILE__, __func__, "OLED not configured");
  if (len < 1 || len > 20)
    ERR__raiseError(__FILE__, __func__, "Bad string length");
  

  const int MAX_FONT_SIZE = 6;
  int horzPixelsNeeded = SCREEN_WIDTH / (len * (LETTER_WIDTH + 1));
  int textSize = min(horzPixelsNeeded, MAX_FONT_SIZE);

  int xPos = SCREEN_WIDTH / 2 - (LETTER_WIDTH + 1) * len * textSize / 2;
  int yPos = SCREEN_HEIGHT / 2 - (LETTER_HEIGHT + 1) * textSize / 2;

  keypadDisplay.clearDisplay();
  keypadDisplay.setTextSize(textSize);
  keypadDisplay.setCursor(xPos, yPos);
  keypadDisplay.print(str);
  keypadDisplay.display();

}

#endif // If include OLED 1
#endif // If OLED_1_H not defined