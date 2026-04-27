#include <Arduino.h>
#include "distance.h"
#include "error.h"
//#include "pin_config.h"

#define TRIG1 13
#define TRIG2 3
#define TRIG3 4

#define ECHO1 A2
#define ECHO2 A1
#define ECHO3 A0


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
				Error::raiseError(__FILE__, __func__, "Bad sensor selected");
		}
	}

}