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

		lcd.init();
		lcd.backlight();
		lcd.clear();

		configured = true;
	}

	void displayWelcome()
	{
		if (!configured)
			Error::raiseError(__FILE__, __func__, "LCD Not initialized");

		lcd.clear();
	  lcd.setCursor(4,0);
	  lcd.print("Welcome!");
	  delay(2000);

	  for (int i = 0; i < 12; i++)
	  {
	    lcd.scrollDisplayLeft();
	    delay(150);
	  }

	  delay(1000);

	  lcd.clear();
	  lcd.setCursor(0, 0);
	  lcd.print("Press any key on");
	  lcd.setCursor(0,1);
	  lcd.print(" keypad to start");
	}

	void printScore(int score)
	{
		if (!configured)
			Error::raiseError(__FILE__, __func__, "LCD Not initialized");
		lcd.clear();
	  lcd.setCursor(0, 0);
	  lcd.print("Score:");
	  int xPos = (score < 10) ? 15 : 14;
	  lcd.setCursor(xPos, 0);
	  lcd.print(score);
	}

	void gameOver(int score, int winScore)
	{
		lcd.clear();
		lcd.setCursor(4,0); 
		lcd.print("You Lost");

		if (score == winScore)
		{
			lcd.setCursor(8, 0);
			lcd.print("Win!"); //Replace Lose -> "You Win!"
		}

		lcd.setCursor(4, 1);
		lcd.print("Score: ");
		lcd.print(score);
	}
}