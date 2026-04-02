#ifndef KEYPAD_H
#define KEYPAD_H


namespace Keypad {
  const char TABLE [4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };


  /**
   * "Private" variables to only be used by the keypad function
   */
  #define COL1 7 // Keypad's pin 3
  #define COL2 5 // Keypad's pin 5
  #define COL3 4 // Keypad's pin 6
  #define COL4 3 // Keypad's pin 7

  #define ROW1 2 // Keypad's pin 8
  #define ROW2 9 // Keypad's pin 1
  #define ROW3 8 // Keypad's pin 2
  #define ROW4 6 // Keypad's pin 4

  bool configured = false;


  /* *******************

    "Private" helper functions that are used only by the above functions

    ******************* */


  // Columns are read in ascending order left to right - i.e 1234 is left -> right
  uint8_t readCols()
  {
    uint8_t bits_cols = 0;
    bits_cols |= (uint8_t)digitalRead(COL1) << 3;
    bits_cols |= (uint8_t)digitalRead(COL2) << 2;
    bits_cols |= (uint8_t)digitalRead(COL3) << 1;
    bits_cols |= (uint8_t)digitalRead(COL4);

    return bits_cols;
  }

  // Rows are read in ascending order going down the keypad - i.e 1234 is top -> bottom
  void writeRows(uint8_t rows)
  {
    digitalWrite(ROW1, (rows & 0b1000));
    digitalWrite(ROW2, (rows & 0b0100));
    digitalWrite(ROW3, (rows & 0b0010));
    digitalWrite(ROW4, (rows & 0b0001));
  }

  // Uses low-order column priority encoding. If multiple columns are pressed, the lower-valued (left-most) column will be accepted
  int resolveColPressed(uint8_t col_reading)
  {
    if ( !(col_reading & 0b1000)) 
      return 1;
    else if (!(col_reading & 0b0100)) 
      return 2;
    else if ( !(col_reading & 0b0010)) 
      return 3;
    else 
      return 4; 
  }

  char getKeyPressed(int row, int col)
  {
    row --;
    col --;

    return TABLE[row][col];
  }



  /**
   * Public keypad and configuration functions
   */

  void configureKeypadPins()
  {
    pinMode(COL1, INPUT);
    pinMode(COL2, INPUT);
    pinMode(COL3, INPUT);
    pinMode(COL4, INPUT);

    pinMode(ROW1, OUTPUT);
    pinMode(ROW2, OUTPUT);
    pinMode(ROW3, OUTPUT);
    pinMode(ROW4, OUTPUT);

    configured = true;
  }

  char scanKeypad()
  {
    //Ensure pins cofigured (configuration function called)
    if (!configured)
      Error::raiseError(__FILE__, __func__, "Keypad settings not configured");

    int col_pressed = 0;
    int row_pressed = 0;
    uint8_t col_reading = readCols();

    // Set all rows low and wait until a key is pressed
    writeRows(0);
    while ( col_reading == 0xF )
    {
      col_reading = readCols();
    }


    col_pressed = resolveColPressed(col_reading);

    // Test each row: set all high and see at which row the column reacts 
    for (int i = 3; i >= 0; i--)
    {
      writeRows(0xF);   //Set all rows high initially
      writeRows(0xF & ~( (uint8_t)1 << i));  

      if (readCols() != 0xF) 
      {
        row_pressed = 4 - i;
        break;
      }

      delay(12); //small debouncing delay
    }

    //Capture the button input until released
    while (readCols() != 0xF);

    return getKeyPressed(row_pressed, col_pressed);
  }


  char pickRandomChar()
  {
    char c = TABLE[random(0,4)][random(0,4)];
    return c;
  }

  void pickRandomString(char * buffer, int len)
  {
    for (int i = 0; i < len; i++)
      buffer[i] = pickRandomChar();
    
    buffer[len] = '\0';
  }

}

#endif