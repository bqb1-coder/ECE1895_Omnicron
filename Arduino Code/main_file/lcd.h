#ifndef LCD_H
#define LCD_H

namespace LCD
{
	bool begin();
	void displayWelcome();
	void printScore(int score);
	void gameOver(int score, int winScore);
}

#endif