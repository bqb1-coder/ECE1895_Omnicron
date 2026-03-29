#include "C:\Users\brade\OneDrive - University of Pittsburgh\Classes 2025-2026 Spring\Junior Design\Bop-It!\Header Files\error.h"
#include "C:\Users\brade\OneDrive - University of Pittsburgh\Classes 2025-2026 Spring\Junior Design\Bop-It!\Header Files\keypad.h"
#include "C:\Users\brade\OneDrive - University of Pittsburgh\Classes 2025-2026 Spring\Junior Design\Bop-It!\Header Files\OLED.h"
#include "C:\Users\brade\OneDrive - University of Pittsburgh\Classes 2025-2026 Spring\Junior Design\Bop-It!\Header Files\game_functions.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  randomSeed(analogRead(A3));
  beginDisplay();

  display.display();
}

void loop() {
  bool passed = keypadChallenge(6);
  digitalWrite(2, !passed);
  while(1);
}

