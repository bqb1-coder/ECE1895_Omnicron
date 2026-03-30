#define RTC__ADDRESS               0x32
#define RTC__TIMER_COUNTER_0_REG   0x0B
#define RTC__TIMER_COUNTER_1_REG   0x0C
#define RTC__EXT_REG               0x0D
#define RTC__FLAG_REG              0x0E
#define RTC__CTRL_REG              0x0F
#define RTC__INT_PERIOD            10 //ms


bool RTC__configured = false;
bool RTC__TIMER_STARTED = false;

volatile bool RTC__INTERRUPT_FLAG = 0;
volatile int RTC__COUNTER = -1;
int RTC__MAX_COUNT = 0;

// *********************************************************

int getRTCCounterValue()
{
  return RTC__COUNTER;
}

// Returns whether the RTC counter variable has maxed out
bool checkRTCCounter()
{
  return getRTCCounterValue() == RTC__MAX_COUNT;
}

void RTC__interruptHandler()
{
  RTC__INTERRUPT_FLAG = 1;
  RTC__COUNTER = min(RTC__MAX_COUNT, RTC__COUNTER+1);
}

void initRTC(int interruptPin, int mode = FALLING)
{
  // delay(500);
	attachInterrupt(digitalPinToInterrupt(interruptPin), RTC__interruptHandler, mode);

  // Disable TE, TIE, and TF
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__EXT_REG);
  Wire.write(0x0);      // Write TE low
  Wire.write(0x0);      // Write TF low
  Wire.write(0x0);      // Write TIE low
  Wire.endTransmission();

  // Set counter value to finalize interrupt period
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__TIMER_COUNTER_0_REG);
  Wire.write(41);       // Set counter value to 41
  Wire.write(0);        // Set upper counter bits to 0
  Wire.endTransmission();

  //Set interrupt enable pin
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__CTRL_REG);
  Wire.write(1 << 4);
  Wire.endTransmission();

  RTC__configured = true;
}

void startRTCTimer(int maximumTime)
{
  // Can't start if timer not configured
  if (!RTC__configured)
    ERR__raiseError(__FILE__, __func__, "RTC not configured"); // For .h file
  
  
  //Get the count value that should be used for the timer length
  //Throw an error or warning if detected bad/unoptimal value
  RTC__MAX_COUNT = maximumTime / RTC__INT_PERIOD - 1;
  RTC__COUNTER = 0;

  if (RTC__MAX_COUNT <= 0)
    ERR__raiseError(__FILE__, __func__, "Bad timer value"); // For .h file

  if (RTC__MAX_COUNT <= 100)
    ERR__raiseWarning(__FILE__, __func__, "Low timer value detected"); // For .h file

  // Begin clock for countdown
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__EXT_REG);
  Wire.write((1 << 4));
  bool end_success = Wire.endTransmission() == 0;

  RTC__TIMER_STARTED = end_success && (readRegisterFrom(RTC__EXT_REG, RTC__ADDRESS) & 16 == 16);
}

//Stop timer but maintains the previous timer settings 
void stopRTCTimer()
{
  // Begin clock for countdown
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__EXT_REG);
  Wire.write(0);
  Wire.endTransmission();
}

//Starts the timer, but uses the previous settings 
bool resumeRTCTimer()
{
  // Begin clock for countdown
  Wire.beginTransmission(RTC__ADDRESS);
  Wire.write(RTC__EXT_REG);
  Wire.write((1 << 4));
  Wire.endTransmission();
}

void resetRTCCounter()
{
  RTC__COUNTER = 0;
}
