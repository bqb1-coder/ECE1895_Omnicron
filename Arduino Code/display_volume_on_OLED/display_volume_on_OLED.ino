#include <Wire.h>

#include "OLED_2.h"
#include "util.h"
#include "VolumeSensor.h"


// Example code for HW484 v0.2: Reading an analog sensor
#define NUM_SAMPLES 800
#define ALPHA .4
#define SCALING_POWER .5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  delay(100);

  OLED2::begin();
  // Timer::begin(int interruptPin)

  pinMode(3, OUTPUT);
}



void loop() {
  bool passed = volumeChallenge(1);
  digitalWrite(3, passed);
  while (1);
}
// X = current reading; Y = prev reading; //a = alpha, the sampling factor



bool volumeChallenge(int difficulty)
{
  randomSeed(analogRead(A0));

  int startTime = millis();
  int maxTime = 5000;

  int rangeBase = 55;
  int rangeWidth = rangeBase - random(0,7);
  int rangeLowerBound = random (25, 60);

  int prevVolume = 0;
  int volume = 0;

  bool inRange = false;

  while (1)
  {
    if (millis() - startTime >= maxTime)
    {
      return inRange;
    }

    // 1. get the raw volume reading
    volume = VolumeSensor::readVolume(prevVolume);

    // 2. Apply LPF on volume reading
    prevVolume = Util::lowPassFilter(volume, prevVolume, ALPHA);

    // 3. Scale volume using a scaling factor (0 <= SF <= 1); 0 -> always 128, 1 -> input vol
    int scaledVolume = VolumeSensor::scaleVolume(prevVolume, SCALING_POWER);
    scaledVolume -= 15;

    // 4. The final volume is the volume value bounded 
    int finalVolume = VolumeSensor::boundVolume(scaledVolume);

    inRange = (finalVolume >= rangeLowerBound) && (finalVolume <= rangeLowerBound + rangeWidth);

    OLED2::showVolumeLevel(rangeLowerBound, rangeWidth, finalVolume);
  }
}
