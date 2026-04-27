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
        for (int i = 1; i <= 3; i++)
            if (Distance::read(i) <= Distance::RANGE) 
                return false;

        return true;
    }
}