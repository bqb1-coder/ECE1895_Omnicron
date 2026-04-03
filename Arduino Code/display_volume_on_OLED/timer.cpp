#include <Arduino.h>
#include <Wire.h>
#include "timer.h"
#include "error.h"
#include "util.h"


namespace Timer {
  bool configured = false;
  bool timerStarted = false;

  volatile bool interruptFlag = 0;
  volatile int counterValue = -1;
  int maxCount = 0;

  // *********************************************************

  int getCounterValue()
  {
    return counterValue;
  }

  // Returns whether the RTC counter variable has maxed out
  bool isTimerExpired()
  {
    return getCounterValue() == maxCount;
  }

  bool isStarted()
  {
    return timerStarted;
  }

  void interruptHandler()
  {
    interruptFlag = 1;
    counterValue = min(maxCount, counterValue+1);
  }

  void begin(int interruptPin, int mode)
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

  void startTimer(int timeSetting)
  {
    // Can't start if timer not configured
    if (!configured)
      Error::raiseError(__FILE__, __func__, "RTC not configured"); // For .h file
    
    
    //Get the count value that should be used for the timer length
    //Throw an error or warning if detected bad/unoptimal value
    maxCount = timeSetting / INT_PERIOD - 1;
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

    Serial.print("end_success: ");
    Serial.println(end_success);
    Serial.println(Util::readRegisterFrom(EXT_REG, ADDRESS));

    timerStarted = end_success;
    Serial.println(timerStarted);
  }

  void stopTimer()
  {
    // Begin clock for countdown
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write(0);
    Wire.endTransmission();

    resetCounter();
    timerStarted = false;
  }

  void pauseTimer()
  {
    // Begin clock for countdown
    Wire.beginTransmission(ADDRESS);
    Wire.write(EXT_REG);
    Wire.write(0);
    Wire.endTransmission();


    timerStarted = false;
  }

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