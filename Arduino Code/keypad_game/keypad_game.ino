#include <Wire.h>

#define INCLUDE_OLED_1
// #define INCLUDE_OLED_2

#include "MAIN_HEADER.h"

// #define SCREEN_ADDRESS 0x3C
#define RTC_INT_PIN        2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

  OLED1::begin();

  // pinMode(2, OUTPUT);
  randomSeed(analogRead(A3));
  Timer::begin(RTC_INT_PIN);

  Timer::startTimer(3000);
  if (!Timer::isStarted())
    Error::raiseError("main", "setup", "timer not started successfully");
}

void loop() {

  bool passed = Games::keypadChallenge(5);
  Timer::stopTimer();
  digitalWrite(2, !passed);
  while(1);
}

