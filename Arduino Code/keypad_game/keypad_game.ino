#include <Wire.h>
#include "MAIN_HEADER.h"

#define SCREEN_ADDRESS 0x3C
#define INT_PIN        2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  randomSeed(analogRead(A3));
  beginDisplay(SCREEN_ADDRESS);
  initRTCTimer(INT_PIN);

  display.display();
}

void loop() {

  bool passed = keypadChallenge(5);
  digitalWrite(2, !passed);
  while(1);
}

