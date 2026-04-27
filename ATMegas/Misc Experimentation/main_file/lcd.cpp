#include "lcd.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "error.h"

namespace LCD
{
	static constexpr int LCD_ADDRESS = 0x27;
	static constexpr int LCD_WIDTH = 16;
	static constexpr int LCD_HEIGHT = 2;

	bool configured = false;

	LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);

	bool begin()
	{
		if (configured)
			return true;

		Serial.print(F("Past IF"));
		lcd.init();
		Serial.print(F("Past init"));
		lcd.backlight();
		Serial.print(F("Past backlight"));
		lcd.clear();
		Serial.print(F("Past clear"));

		configured = true;
		return configured;
	}

	void displayWelcome()
	{
		if (!configured)
			Error::raiseError(__FILE__, __func__, "LCD Not initialized");

		lcd.clear();
	  lcd.setCursor(4,0);
	  lcd.print(F("Welcome!"));
	  delay(2000);

	  for (int i = 0; i < 12; i++)
	  {
	    lcd.scrollDisplayLeft();
	    delay(150);
	  }

	  delay(1000);

	  lcd.clear();
	  lcd.setCursor(0, 0);
	  lcd.print(F("Press any key on"));
	  lcd.setCursor(0,1);
	  lcd.print(F(" keypad to start"));
	}

	void printScore(int score)
	{
		if (!configured)
			Error::raiseError(__FILE__, __func__, "LCD Not initialized");
		lcd.clear();
	  lcd.setCursor(0, 0);
	  lcd.print(F("Score:"));
		Serial.print(score);
	  int xPos = (score < 10) ? 15 : 14;
	  lcd.setCursor(xPos, 0);
	  lcd.print(score);
	}

	void gameOver(int score, int winScore)
	{
		lcd.clear();
		lcd.setCursor(4,0); 
		lcd.print(F("You Lost"));

		if (score == winScore)
		{
			lcd.setCursor(8, 0);
			lcd.print(F("Win!")); //Replace Lose -> "You Win!"
		}

		lcd.setCursor(4, 1);
		lcd.print(F("Score: "));
		lcd.print(score);
	}
}