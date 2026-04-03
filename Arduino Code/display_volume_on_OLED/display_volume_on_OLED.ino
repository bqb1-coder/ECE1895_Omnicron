#include <Wire.h>

#include "OLED_2.h"
#include "util.h"


// Example code for HW484 v0.2: Reading an analog sensor
#define NUM_SAMPLES 800
#define ALPHA .4
#define SCALING_POWER .55


int prevVolume = 0;
int volume = 0;
int maximumVolumeReached = 0;

int leftBound = 35; //random(10, 65);
int width = 65; //random(78, 118);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  delay(500);

  OLED2::begin();

  randomSeed(analogRead(A0));
}

void loop() {
  // put your main code here, to run repeatedly:
  int maxVal = 0;
  int minVal = 128;
  int aRead = 0;
  
  // prevVolume = volume;

  for (int i = 0; i < NUM_SAMPLES ; i++) {
    aRead = analogRead(A0);
    maxVal = max(maxVal, aRead);
    minVal = min(minVal, aRead);
  }

  volume = maxVal - minVal;

  prevVolume = Util::lowPassFilter(volume, prevVolume, ALPHA);
  Serial.println(volume);

  int scaledVol = round( pow(prevVolume / 128.0, SCALING_POWER) * 128 );

  int boundedVol = scaledVol > 128 ? 128 : scaledVol;

  OLED2::showVolumeLevel(leftBound, width, boundedVol);

}

// X = current reading; Y = prev reading; //a = alpha, the sampling factor
