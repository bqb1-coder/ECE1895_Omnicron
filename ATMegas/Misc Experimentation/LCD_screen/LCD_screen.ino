#include <LiquidCrystal_I2C.h>
#include "keypad.h"
#include "lcd.h"

void setup() {
  // put your setup code here, to run once:
  LCD::begin();
  for (int i = 0 ; i < 100 ; i ++)
  {
    LCD::gameOver(i, 99);
    delay(250);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
