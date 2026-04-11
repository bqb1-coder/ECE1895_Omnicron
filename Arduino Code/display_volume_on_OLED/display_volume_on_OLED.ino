#include <Wire.h>

#include "OLED_2.h"
#include "util.h"
#include "VolumeSensor.h"
#include "game_functions.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  delay(100);

  OLED2::begin();
  // Timer::begin(interruptPin)

  pinMode(3, OUTPUT);
}



void loop() {
  bool passed = Games::volumeChallenge();
  digitalWrite(3, passed);
  while (1);
}
// X = current reading; Y = prev reading; //a = alpha, the sampling factor

