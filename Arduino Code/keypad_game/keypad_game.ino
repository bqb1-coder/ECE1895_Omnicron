#include <Wire.h>

// #define INCLUDE_OLED_1
// #define INCLUDE_OLED_2

#include "error.h"
#include "game_functions.h"
#include "keypad.h"
#include "OLED_1.h"
#include "timer.h"
#include "util.h"

// #define SCREEN_ADDRESS 0x3C
#define RTC_INT_PIN       2
#define OUT_PIN           3

int numberKeypadSymbols = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

  OLED1::begin();

  pinMode(OUT_PIN, OUTPUT);
  randomSeed(analogRead(A3));
  Timer::begin(RTC_INT_PIN);

  Timer::startTimer(5000);
  if (!Timer::isStarted())
    Error::raiseError("main", "setup", "timer not started successfully");
}

void loop() {

  bool passed = Games::keypadChallenge(numberKeypadSymbols);
  Timer::stopTimer();
  digitalWrite(3, !passed);
  while(1);
}

