#ifndef IDOLS_H
#define IDOLS_H

#include "pin_config.h"

namespace Idols
{
	enum LEDColor {
		RED, 
		BLUE,
		NONE
	};

	using IdolColor = LEDColor; // Create an alias for LEDColor

	IdolColor pickFirstIdolColor();
	IdolColor pickSecondIdolColor(IdolColor used);
	IdolColor pickThirdIdolColor(IdolColor used1, IdolColor used2);
	void setLEDToColor(int LEDNum, LEDColor ledcolor);
	void setAllLEDColors(LEDColor LED1, LEDColor LED2, LEDColor LED3);
	bool matchReadings(int reedPin, int hallEffectPin, IdolColor color);
	void flashLEDs(bool correct);
}

#endif