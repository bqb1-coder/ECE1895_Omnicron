#include "Audio.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Audio::init();
  Audio::setVolume(20);
  Audio::playTrack(Track::INDIE);
  delay(3000);
  Audio::playTrack(Track::LOSE);
  delay(3000);
  Audio::playTrack(Track::OFFER);
  delay(3000);
  Audio::playTrack(Track::CHANT);
  delay(3000);
  Audio::playTrack(Track::HACK);
  delay(3000);
  Audio::playTrack(Track::WHIP);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
