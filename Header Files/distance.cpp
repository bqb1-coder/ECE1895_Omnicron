#include <Arduino.h>
#include "distance.h"
#include "error.h"

#define TRIG1 13
#define TRIG2 3
#define TRIG3 4

#define ECHO1 A2
#define ECHO2 A1
#define ECHO3 A0

namespace Distance
{
	read(int sensorNum)
	{
		switch (sensorNum) {
			case 1:
				return sensor1.ping_cm();
			case 2:
				return sensor2.ping_cm();
			case 3:
				return sensor3.ping_cm();
			default:
				Error::raiseError(__FILE__, __func__, "Bad sensor selected");
		}
	}

}