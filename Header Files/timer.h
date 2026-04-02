#ifndef TIMER_H
#define TIMER_H

namespace Timer {

  static constexpr uint8_t ADDRESS = 0x32;
  static constexpr uint8_t  TIMER_counterValue_0_REG = 0x0B;
  static constexpr uint8_t  TIMER_counterValue_1_REG = 0x0C;
  static constexpr uint8_t  EXT_REG = 0x0D;
  static constexpr uint8_t  FLAG_REG = 0x0E;
  static constexpr uint8_t  CTRL_REG = 0x0F;
  static constexpr uint8_t  INT_PERIOD = 10; //ms

  // RTC Timer initialization 
  void begin(int interruptPin, int mode = FALLING);

  // Returns the value of the timer counter
  int getCounterValue();

  // Returns whether the RTC counter variable has maxed out
  bool isTimerExpired();

  // Returns whether the timer has been started and has not been stopped by interface
  bool isStarted();

  // Handles the interrupt
  void interruptHandler();

  //Starts the timer with the given time value (in ms)
  void startTimer(int timeSetting);

  //Stops the timer and sets it to zero, but maintains the previous timer settings 
  void stopTimer();

  //Pauses the timer but keeps the current counter value
  void pauseTimer();

  //Starts the timer, but uses the previous settings 
  bool resumeTimer();

  // Resets the counter and therefore the timer
  void resetCounter();

}


#endif