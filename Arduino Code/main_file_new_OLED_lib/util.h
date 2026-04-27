#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <stdint.h>
#include "error.h"

enum Challenge {
  KEYPAD,
  IDOLS,
  AUDIO
};

namespace Util {
  void clearSerialBuffer();
  void writeRegisterTo(uint8_t reg, uint8_t val, int slave_address);
  uint8_t readRegisterFrom(uint8_t reg, int slave_address);
  float lowPassFilter(float X, float Y, float a);
  int updateEEPROM(int address = 0);
  bool activateSurprise(float chance);
  float determineChance(int score);
  Challenge chooseChallenge();
}

#endif