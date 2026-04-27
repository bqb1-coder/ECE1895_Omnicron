#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "game_functions.h"

#include "OLED_2.h"


#include "util.h"
#include "VolumeSensor.h"
#include "idols.h"
#include "pin_config.h"

#include "state_action.h"

namespace Games {
    bool volumeChallenge(volatile State* curState)
    {
        int rangeBase = 55;
        int rangeWidth = rangeBase + (random(0,20) - 10);
        int rangeLowerBound = random (20, 50);

        int prevVolume = 0;
        int volume = 0;
        // int mappedVol = 0;  //Analog read goes from 0-2.5V or 0 to 511

        bool inRange = false;


        while (*curState == State::EXEC)
        {
            //Read the sensor volume
            volume = VolumeSensor::readVolume();

            //apply EWMA, shift volume down, and bound it between 0 and 128
            volume = Util::lowPassFilter(volume, prevVolume, VolumeSensor::ALPHA);
            volume -= 20;
            volume = VolumeSensor::boundVolume(volume);

            inRange = (volume >= rangeLowerBound) && (volume <= rangeLowerBound + rangeWidth);

            // OLED2::clearVolumeLevel(prevVolume);
            OLED2::showVolumeLevel(rangeLowerBound, rangeWidth, volume);
            
            prevVolume = volume;
        }

        OLED2::clearDisplay();

        return inRange;
    }

    bool idolChallenge(volatile State* curState)
    {
        //Pick colors for each spot and display to LEDs
        Idols::IdolColor pos1 = Idols::pickFirstIdolColor();
        Idols::IdolColor pos2 = Idols::pickSecondIdolColor(pos1);
        Idols::IdolColor pos3 = Idols::pickThirdIdolColor(pos1, pos2);
        Idols::setAllLEDColors(pos1, pos2, pos3);

        while (*curState == State::EXEC);

        bool pos1Good = Idols::matchReadings(REED1, HALL1, pos1);
        bool pos2Good = Idols::matchReadings(REED2, HALL2, pos2);
        bool pos3Good = Idols::matchReadings(REED3, HALL3, pos3);

        bool allGood = pos1Good && pos2Good && pos3Good;
        Idols::flashLEDs(allGood);
        return allGood;
    }
}