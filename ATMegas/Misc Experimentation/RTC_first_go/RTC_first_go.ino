#include <Wire.h>

#define RTC_ADDRESS               0x32
#define RTC_TIMER_COUNTER_0_REG   0x0B
#define RTC_TIMER_COUNTER_1_REG   0x0C
#define RTC_EXT_REG               0x0D
#define RTC_FLAG_REG              0x0E
#define RTC_CTRL_REG              0x0F

#define INT_PIN                   2
#define OUT_PIN                   3
// Write below to 0 (in order) 
//   TE - EXT_R[4], 
//   TIE - CTRL_R[4], 
//   TF - FLAG_R[4] 
// Choose clock freq, write to TD
// choose countdown period and write corresp. value to timer counter 0/1
// Set TIE to 1 get interrupt on INT pin
// Set TE to 1 to start countdown timer

volatile byte interrupt = 0;
int count = 0;
bool out_pin = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(INT_PIN), interruptHandler, RISING);


  // Disable TE, TIE, and TF
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(RTC_EXT_REG);
  Wire.write(0x0);      // Write TE low
  Wire.write(0x0);      // Write TF low
  Wire.write(0x0);      // Write TIE low
  Wire.endTransmission(); 

  // Choose clock freq - redundant, set when writing 0 to EXT reg
  /*
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(RTC_EXT_REG);
  Wire.write(0x0);      // Set clock freq = 4096Hz
  Wire.endTransmission();
  // */

  // Set counter value to finalize interrupt period
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(RTC_TIMER_COUNTER_0_REG);
  Wire.write(41);       // Set counter value to 41
  Wire.write(0);        // Set upper counter bits to 0
  Wire.endTransmission();

  //Set interrupt enable pin
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(RTC_CTRL_REG);
  Wire.write(1 << 4);
  Wire.endTransmission();

  // Begin clock for countdown
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(RTC_EXT_REG);
  Wire.write( (1 << 4));
  Wire.endTransmission();
}

byte flag_reg = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while (1)
  {
    if (interrupt)
    {
      // Wire.beginTransmission(RTC_ADDRESS);
      // Wire.write(RTC_FLAG_REG);
      // Wire.endTransmission(false);
      // Wire.requestFrom(RTC_ADDRESS, 1);
      // flag_reg = Wire.read();

      // Serial.println(flag_reg);

      // // Clear TIE in flag register
      // flag_reg &= ~(1 << 4);

      // // Write the new flag data back to flag reg
      // Wire.beginTransmission(RTC_ADDRESS);
      // Wire.write(RTC_FLAG_REG);
      // Wire.write(flag_reg);
      // Wire.endTransmission();

      // Wire.beginTransmission(RTC_ADDRESS);
      // Wire.write(RTC_FLAG_REG);
      // Wire.endTransmission(false);
      // Wire.requestFrom(RTC_ADDRESS, 1);
      // flag_reg = Wire.read();

      // Serial.println(flag_reg);

      // count++;
      // // Serial.println(count);
  
      out_pin = !out_pin;
      digitalWrite(OUT_PIN, !out_pin);
      interrupt = 0;
    }
  }
}
// 5 sec = 5000 ms / (10ms / int) = 500 int
void interruptHandler()
{
  interrupt = 1;

}
