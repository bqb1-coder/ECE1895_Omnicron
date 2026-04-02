#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "timer.h"

namespace Games {
  bool keypadChallenge(int stringLength, int maxTime = 5000);
}
#endif