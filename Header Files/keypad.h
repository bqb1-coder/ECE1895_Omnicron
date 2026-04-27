#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include "pin_config.h"

namespace Keypad {
  static constexpr char TABLE PROGMEM [4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };


  // Columns are read in ascending order left to right - i.e 1234 is left -> right
  uint8_t readCols();

  // Rows are read in ascending order going down the keypad - i.e 1234 is top -> bottom
  void writeRows(uint8_t rows);

  // Uses low-order column priority encoding. If multiple columns are pressed, the lower-valued (left-most) column will be accepted
  int resolveColPressed(uint8_t col_reading);

  char getKeyPressed(int row, int col);


  /**
   * Public keypad and configuration functions
   */

  void configureKeypadPins();

  char scanKeypad();

  char pickRandomChar();

  void pickRandomString(char * buffer, int len);

  void awaitGameStart();

}

#endif