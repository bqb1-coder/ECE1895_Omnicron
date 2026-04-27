#include <Arduino.h>
#include "idols.h"
#include "pin_config.h"

namespace Idols
{
	//Each idol has different set of available spots, handle each separately

	//First slot
	IdolColor pickFirstIdolColor()
	{
	  IdolColor options[3] = {RED, BLUE, NONE};
	  return options[random(0,2 +1)]; //0 to 2
	}

	//Second slot
	IdolColor pickSecondIdolColor(IdolColor used)
	{
	  IdolColor options[3] = {RED, BLUE, NONE};

	  switch (used)
	  {
	    case RED:
	      return options[random(1,2 +1)]; //1 or 2
	    case BLUE:
	      return options[random(0,1 +1) * 2]; //(0 or 1) * 2 -> 0 or 2 
	    default:
	      return options[random(0,1 +1)]; //0 or 1
	  }
	}

	IdolColor pickThirdIdolColor(IdolColor used1, IdolColor used2)
	{
	  //Sum uses enum values of idol colors, RED=0, BLUE=1, NONE=2
	  // 0+1 = 1 -> pick NONE
	  // 0+2 = 2 -> pick BLUE
	  // 1+2 = 3 -> pick RED

	  // This options array is different from previous ones on purpose
	  IdolColor options[3] = {NONE, BLUE, RED};
	  int sum = used1 + used2;
	  return options[sum-1];
	}

	//Set a specific LED # to a given color
	void setLEDToColor(int LEDNum, LEDColor ledcolor)
	{
	  int redPin;
	  int bluePin;

	  switch (LEDNum) {
	    case 1:
	      redPin = RED1;
	      bluePin = BLUE1;
	      break;
	    case 2:
	      redPin = RED2;
	      bluePin = BLUE2;
	      break;
	    case 3:
	      redPin = RED3;
	      bluePin = BLUE3;
	      break;
	  }

	  int redLogicVal = ledcolor == RED ? HIGH : LOW;
	  int blueLogicVal = ledcolor == BLUE ? HIGH : LOW;

	  digitalWrite(redPin, redLogicVal);
	  digitalWrite(bluePin, blueLogicVal);
	}

	//Can set all three LEDs to a specified color
	void setAllLEDColors(LEDColor LED1, LEDColor LED2, LEDColor LED3)
	{
	  setLEDToColor(1, LED1);
	  setLEDToColor(2, LED2);
	  setLEDToColor(3, LED3);
	}

	//Match the readings for the reed switch and hall effect sensor to a given color
	bool matchReadings(int reedPin, int hallEffectPin, IdolColor color)
	{
	  int correctReedValue = HIGH;
	  int correctHallValue = LOW;

	  switch (color)
	  {
	    case RED: // Reed HIGH, Hall LOW
	      break;
	    case BLUE: // Reed HIGH, Hall HIGH
	      correctHallValue = HIGH;
	      break;
	    case NONE: // Reed LOW, Hall HIGH
	      correctReedValue = LOW;
	      correctHallValue = HIGH;
	      break;
	  }

	  return (digitalRead(reedPin) == correctReedValue) && (digitalRead(hallEffectPin) == correctHallValue);
	}

	//Flash LEDs BLUE if configuration is correct and RED if not 
	void flashLEDs(bool correct)
	{
	  const int flashTime = 150;
	  LEDColor color = BLUE;
	  if (!correct)
	    color = RED;
	  
	  setAllLEDColors(color, color, color);
	  delay(flashTime);
	  setAllLEDColors(NONE, NONE, NONE);
	  delay(flashTime);
	  setAllLEDColors(color, color, color);
	  delay(flashTime);
	  setAllLEDColors(NONE, NONE, NONE);
	  delay(flashTime);
	}

}
