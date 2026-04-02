#include <Wire.h>

// #define INCLUDE_OLED_1
// #define INCLUDE_OLED_2

#include "MAIN_HEADER.h"

// #define SCREEN_ADDRESS 0x3C
#define RTC_INT_PIN        2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(2, OUTPUT);
  randomSeed(analogRead(A3));
  initRTC(RTC_INT_PIN);

  startRTCTimer(3000);
  if (!isTimerStarted())
    ERR__raiseError("main", "setup", "timer not started successfully");
}

void loop() {

  bool passed = keypadChallenge(5);
  stopRTCTimer();
  digitalWrite(2, !passed);
  while(1);
}

