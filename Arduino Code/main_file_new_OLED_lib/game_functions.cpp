#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "game_functions.h"
#include "OLED_1.h"
// #include "OLED_2.h"
#include "keypad.h"
#include "timer.h"
#include "util.h"
// #include "VolumeSensor.h"
// #include "idols.h"
#include "pin_config.h"
#include "distance.h"
#include "UARTx.h"

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
            OLED1::clear();
            return false;
          }
          
          pressedChar = '-'; // reset to random character each iteration

          //Check if a character has come in on serial line and read it if so
          pressedChar = Keypad::scanKeypad();

          if (pressedChar == '-')
            continue;
          

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
            OLED1::clear();
            return false;
          }

          // Write current string to screen
          OLED1::printCenteredString(displayString);

          //When they get all correct, loop back around and go again
          if (numCorrect == stringLength)
          {
            OLED1::clear();
            return true;
          }
        }
    }


    bool volumeChallenge()
    {
        UARTx::sendCommand(UARTx::CMD_VOLUME_GAME);
        return UARTx::awaitResponse();
    }

    bool idolChallenge()
    {
        UARTx::sendCommand(UARTx::CMD_IDOLS_GAME);
        return UARTx::awaitResponse();
    }

    bool avoidChallenge()
    {
        int i = 3;
        // for (int i = 1; i <= 3; i++)
        // {

            int readVal = Distance::read(i); //reading third usonic sensor
            Serial.print(F("\nSonar "));
            Serial.print(i);
            Serial.print(": ");
            Serial.println(readVal);
            if (readVal <= Distance::RANGE) 
                return false;
        // }

        return true;
    }
}