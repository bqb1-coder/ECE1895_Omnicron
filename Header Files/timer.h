#ifndef TIMER_H
#define TIMER_H

namespace Timer {

  #define ADDRESS               0x32
  #define TIMER_counterValue_0_REG   0x0B
  #define TIMER_counterValue_1_REG   0x0C
  #define EXT_REG               0x0D
  #define FLAG_REG              0x0E
  #define CTRL_REG              0x0F
  #define INT_PERIOD            10 //ms


  bool configured = false;
  bool timerStarted = false;

  volatile bool interruptFlag = 0;
  volatile int counterValue = -1;
  int maxCount = 0;

  // *********************************************************

  int getRTCCounterValue()
  {
    return counterValue;
  }

  // Returns whether the RTC counter variable has maxed out
  bool RTCTimerExpired()
  {
    return getRTCCounterValue() == maxCount;
  }

  bool isTimerStarted()
  {
    return timerStarted;
  }

  void interruptHandler()
  {
    interruptFlag = 1;
    counterValue = min(maxCount, counterValue+1);
  }

  void initRTC(int interruptPin, int mode = FALLING)
  {
    // delay(500);
  	attachInterrupt(digitalPinToInterrupt(interruptPin), interruptHandler, mode);

    // Disable TE, TIE, and TF
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write(0x0);      // Write TE low
    Wire.write(0x0);      // Write TF low
    Wire.write(0x0);      // Write TIE low
    Wire.endTransmission();

    // Set counter value to finalize interrupt period
    Wire.beginTransmission(ADDRESS);
    Wire.write(TIMER_counterValue_0_REG);
    Wire.write(41);       // Set counter value to 41
    Wire.write(0);        // Set upper counter bits to 0
    Wire.endTransmission();

    //Set interrupt enable pin
    Wire.beginTransmission(ADDRESS);
    Wire.write(CTRL_REG);
    Wire.write(1 << 4);
    Wire.endTransmission();

    configured = true;
  }

  void startTimer(int maximumTime)
  {
    // Can't start if timer not configured
    if (!configured)
      Error::raiseError(__FILE__, __func__, "RTC not configured"); // For .h file
    
    
    //Get the count value that should be used for the timer length
    //Throw an error or warning if detected bad/unoptimal value
    maxCount = maximumTime / INT_PERIOD - 1;
    counterValue = 0;

    if (maxCount <= 0)
      Error::raiseError(__FILE__, __func__, "Bad timer value"); // For .h file

    if (maxCount <= 100)
      Error::raiseWarning(__FILE__, __func__, "Low timer value detected"); // For .h file

    // Begin clock for countdown
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write((1 << 4));
    bool end_success = Wire.endTransmission() == 0;

    timerStarted = end_success && (Util::readRegisterFrom(EXT_REG, ADDRESS) & 16 == 16);
  }

  //Stop timer but maintains the previous timer settings 
  void stopTimer()
  {
    // Begin clock for countdown
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write(0);
    Wire.endTransmission();
  }

  //Starts the timer, but uses the previous settings 
  bool resumeTimer()
  {
    // Begin clock for countdown
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write((1 << 4));
    Wire.endTransmission();
  }

  void resetCounter()
  {
    counterValue = 0;
  }

}


#endif