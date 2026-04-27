#include <Arduino.h>
#include "distance.h"
#include "error.h"
#include "pin_config.h"

namespace Distance
{
	NewPing sonar1(TRIG1, ECHO1, MAX_DISTANCE);
	NewPing sonar2(TRIG2, ECHO2, MAX_DISTANCE);
	NewPing sonar3(TRIG3, ECHO3, MAX_DISTANCE);


	int read(int sensorNum)
	{
		switch (sensorNum) {
			case 1:
				return sonar1.ping_cm();
			case 2:
				return sonar2.ping_cm();
			case 3:
				return sonar3.ping_cm();
			default:
				Error::raiseError(F(__FILE__), NULL, F("Bad sensor selected"));
		}
	}

}