#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "game_functions.h"
// #include "pin_config.h"
#include "distance.h"

namespace Games {
    bool avoidChallenge()
    {
        for (int i = 1; i <= 3; i++)
            if (Distance::read(i) <= Distance::RANGE) 
                return false;

        return true;
    }
}