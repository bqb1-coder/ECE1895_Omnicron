#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <stdint.h>

namespace Util {
  void clearSerialBuffer();
  void writeRegisterTo(uint8_t reg, uint8_t val, int slave_address);
  uint8_t readRegisterFrom(uint8_t reg, int slave_address);
}

#endif