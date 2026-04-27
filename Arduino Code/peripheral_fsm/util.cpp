#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "util.h"


namespace Util {
  #define UART_INIT_COMMS 		0x55  // 0101 0101
  #define UART_MASTER_ID  		0x65  // 0110 0101
  #define UART_PERIPH1_ID 		0xA5  // 1010 0101

  void clearSerialBuffer()
  {
  	while (Serial.available() > 0) Serial.read();
  }

  // Byte 1 = 01010101
  // Byte 2 = 01010101
  // Byte 3 = Peripheral ID
  // Byte 4 = Command


  void writeRegisterTo(uint8_t reg, uint8_t val, int slave_address)
  {
    Wire.beginTransmission(slave_address);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
  }

  uint8_t readRegisterFrom(uint8_t reg, int slave_address)
  {
    Wire.beginTransmission(slave_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(slave_address, 1);
    return Wire.read();
  }

  //Perform an exponentially weighted moving average filter
  float lowPassFilter(float X, float Y, float a)
  {
    return X + a * (Y - X); //EWMA Filter formula
  }

  int updateEEPROM(int address)
  {
    int reading = EEPROM.read(address);
    EEPROM.write(address, (reading + 1) % 256);
    return reading;
  }

  bool activateSurprise(float chance)
  {
    const int DIV = 100000;
    return (random(0, DIV+1) / (float)DIV) <= chance;
  }

  float determineChance(int score)
  {
    return .095 + ((score / 5) / 200.0);
  }

  
  Challenge chooseChallenge()
  {
    int rand = random(3); // random 0 to 2
    switch (rand)
    {
      case 0:
        return KEYPAD;
      case 1:
        return IDOLS;
      case 2:
        return AUDIO;
      default:
        Error::raiseError(F(__FILE__), NULL, F("Bad random number picked"));
    }
  }

}
