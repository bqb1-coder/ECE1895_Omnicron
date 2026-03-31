#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define SCREEN_ADDRESS 0x3C
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 7

bool OLED__configured = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void beginDisplay(int SCREEN_ADDRESS) {
  delay(500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    ERR__raiseError(__FILE__, __func__, "SSD1306 Allocation failed");
  }

  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  OLED__configured = true;
}

void printCenteredChar(char c, int textSize)
{
  if (!OLED__configured)
    ERR__raiseError(__FILE__, __func__, "OLED not configured");

  display.setTextSize(textSize);
  display.setCursor(SCREEN_WIDTH / 2 - LETTER_WIDTH * textSize / 2, SCREEN_HEIGHT / 2 - LETTER_HEIGHT * textSize / 2);
  display.print(c);
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

  display.setTextSize(textSize);
  display.setCursor(xPos, yPos);
  display.print(str);

}
