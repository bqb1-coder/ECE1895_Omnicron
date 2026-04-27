#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <Arduino.h>
#include <stdint.h>
#include "pin_config.h"
#include "state_action.h"

namespace Games {
  bool keypadChallenge(int stringLength);
  bool volumeChallenge(volatile State* curState);
  bool idolChallenge(volatile State* curState);
  bool avoidChallenge();
}
#endif