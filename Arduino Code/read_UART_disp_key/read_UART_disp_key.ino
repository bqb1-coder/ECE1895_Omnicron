#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 7
#define TEXT_SIZE 6

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
byte data;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(true); // Don't proceed, loop forever
  }

  // Config display
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.invertDisplay(false);
  // printCenteredChar('B', 6);
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    display.clearDisplay();
    data = Serial.read();
    printCenteredChar((char) data, TEXT_SIZE);
    display.display();
  }
}

void printCenteredChar(char c, int textSize)
{
  display.setTextSize(textSize);
  display.setCursor(64 - LETTER_WIDTH * textSize / 2, 32 - LETTER_HEIGHT * textSize / 2);
  display.print(c);
}
