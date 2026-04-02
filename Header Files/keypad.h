#ifndef KEYPAD_H
#define KEYPAD_H


namespace Keypad {
  static constexpr char TABLE [4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };


  /**
   * "Private" variables to only be used by the keypad function
   */
  static constexpr int COL1 = 7 // Keypad's pin 3
  static constexpr int COL2 = 5 // Keypad's pin 5
  static constexpr int COL3 = 4 // Keypad's pin 6
  static constexpr int COL4 = 3 // Keypad's pin 7

  static constexpr int ROW1 = 2 // Keypad's pin 8
  static constexpr int ROW2 = 9 // Keypad's pin 1
  static constexpr int ROW3 = 8 // Keypad's pin 2
  static constexpr int ROW4 = 6 // Keypad's pin 4

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

}

#endif