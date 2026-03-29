
const char KP__TABLE [4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


/**
 * "Private" variables to only be used by the keypad function
 */
#define KP__COL1 7 // Keypad's pin 3
#define KP__COL2 5 // Keypad's pin 5
#define KP__COL3 4 // Keypad's pin 6
#define KP__COL4 3 // Keypad's pin 7

#define KP__ROW1 2 // Keypad's pin 8
#define KP__ROW2 9 // Keypad's pin 1
#define KP__ROW3 8 // Keypad's pin 2
#define KP__ROW4 6 // Keypad's pin 4

bool KP__configured = false;


/* *******************

  "Private" helper functions that are used only by the above functions

  ******************* */


// Columns are read in ascending order left to right - i.e 1234 is left -> right
uint8_t KP__readCols()
{
  uint8_t bits_cols = 0;
  bits_cols |= (uint8_t)digitalRead(KP__COL1) << 3;
  bits_cols |= (uint8_t)digitalRead(KP__COL2) << 2;
  bits_cols |= (uint8_t)digitalRead(KP__COL3) << 1;
  bits_cols |= (uint8_t)digitalRead(KP__COL4);

  return bits_cols;
}

// Rows are read in ascending order going down the keypad - i.e 1234 is top -> bottom
void KP__writeRows(uint8_t rows)
{
  digitalWrite(KP__ROW1, (rows & 0b1000));
  digitalWrite(KP__ROW2, (rows & 0b0100));
  digitalWrite(KP__ROW3, (rows & 0b0010));
  digitalWrite(KP__ROW4, (rows & 0b0001));
}

// Uses low-order column priority encoding. If multiple columns are pressed, the lower-valued (left-most) column will be accepted
int KP__resolveColPressed(uint8_t col_reading)
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

char KP__getKeyPressed(int row, int col)
{
  row --;
  col --;

  return KP__TABLE[row][col];
}



/**
 * Public keypad and configuration functions
 */

void configureKeypadPins()
{
  pinMode(KP__COL1, INPUT);
  pinMode(KP__COL2, INPUT);
  pinMode(KP__COL3, INPUT);
  pinMode(KP__COL4, INPUT);

  pinMode(KP__ROW1, OUTPUT);
  pinMode(KP__ROW2, OUTPUT);
  pinMode(KP__ROW3, OUTPUT);
  pinMode(KP__ROW4, OUTPUT);

  KP__configured = true;
}

char scanKeypad()
{
  //Ensure pins cofigured (configuration function called)
  if (!KP__configured)
  ERR__raiseError(__FILE__, __func__, "Keypad settings not configured");

  int col_pressed = 0;
  int row_pressed = 0;
  uint8_t col_reading = KP__readCols();

  // Set all rows low and wait until a key is pressed
  KP__writeRows(0);
  while ( col_reading == 0xF )
  {
    col_reading = KP__readCols();
  }


  col_pressed = KP__resolveColPressed(col_reading);

  // Test each row: set all high and see at which row the column reacts 
  for (int i = 3; i >= 0; i--)
  {
    KP__writeRows(0xF);   //Set all rows high initially
    KP__writeRows(0xF & ~( (uint8_t)1 << i));  

    if (KP__readCols() != 0xF) 
    {
      row_pressed = 4 - i;
      break;
    }

    delay(12); //small debouncing delay
  }

  //Capture the button input until released
  while (KP__readCols() != 0xF);

  return KP__getKeyPressed(row_pressed, col_pressed);
}


char pickRandomChar()
{
  return KP__TABLE[random(0,4)][random(0,4)];
}

String pickRandomString(int len)
{
  String str = "";

  for (int i = 0; i < len; i++)
    str += pickRandomChar();

  return str;
}

