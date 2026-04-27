#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <Arduino.h>
#include <stdint.h>
#include "pin_config.h"

namespace Games {
  bool keypadChallenge(int stringLength);
  bool volumeChallenge();
  bool idolChallenge();
  bool avoidChallenge();
}
#endif