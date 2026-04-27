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
#include "idols.h"
#include "pin_config.h"
#include "distance.h"

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

    bool idolChallenge()
    {
        //Pick colors for each spot and display to LEDs
        Idols::IdolColor pos1 = Idols::pickFirstIdolColor();
        Idols::IdolColor pos2 = Idols::pickSecondIdolColor(pos1);
        Idols::IdolColor pos3 = Idols::pickThirdIdolColor(pos1, pos2);
        Idols::setAllLEDColors(pos1, pos2, pos3);

        delay(5000);

        bool pos1Good = Idols::matchReadings(REED1, HALL1, pos1);
        bool pos2Good = Idols::matchReadings(REED2, HALL2, pos2);
        bool pos3Good = Idols::matchReadings(REED3, HALL3, pos3);

        bool allGood = pos1Good && pos2Good && pos3Good;
        Idols::flashLEDs(allGood);
        return allGood;
    }

    bool avoidChallenge()
    {
        for (int i = 1; i <= 3; i++)
            if (Distance::read(i) <= Distance::RANGE) 
                return false;

        return true;
    }
}