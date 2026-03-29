#include "C:\Users\brade\OneDrive - University of Pittsburgh\Classes 2025-2026 Spring\Junior Design\Bop-It!\Header Files\keypad.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  configureKeypadPins();
}

void loop() {
  char pressedChar = scanKeypad();
  Serial.write(pressedChar);
}
