#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "game_functions.h"
#include "OLED_1.h"
#include "OLED_2.h"
#include "keypad.h"
#include "timer.h"
#include "util.h"
#include "VolumeSensor.h"

namespace Games {
  bool keypadChallenge(int stringLength)
  {
    char pressedChar = '-';

    char displayString[stringLength+1];
    char randomString[stringLength+1];

    int numCorrect = 0;

    //Pick a new random string of characters
    Keypad::pickRandomString(randomString, stringLength);
    strcpy(displayString, randomString);

    numCorrect = 0;

    // Write current string to screen
    OLED1::printCenteredString(displayString);


    //Enter the challenge
    while (1)
    {
      //Check the timer, end if over time
      if (Timer::isTimerExpired())
      {
        return false;
      }
      
      pressedChar = '-'; // reset to random character each iteration

      //Check if a character has come in on serial line and read it if so
      if (Serial.available() > 0)
      {
        pressedChar = Serial.read();
      }

      // If no key pressed (at default value) just continue to next iteration
      if (pressedChar == '-')
        continue;

      // If they get the key correct 
      if (pressedChar == randomString[numCorrect])
      {
        displayString[numCorrect] = ' ';
        numCorrect++;
      }
      else //If not, return false;
      {
        return false;
      }

      // Write current string to screen
      OLED1::printCenteredString(displayString);

      //When they get all correct, loop back around and go again
      if (numCorrect == stringLength)
        return true;
    }
  }


  bool volumeChallenge()
  {
    const float ALPHA = .5;
    const float SCALING_POWER = .55; 
    randomSeed(analogRead(A0) * millis());

    int startTime = millis();
    int maxTime = 5000;

    int rangeBase = 55;
    int rangeWidth = rangeBase + (random(0,20) - 10);
    int rangeLowerBound = random (20, 50);

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
}