#ifndef DISTANCE_H
#define DISTANCE_H

#include <Arduino.h>
#include <NewPing.h>

namespace Distance
{
	static constexpr int MAX_DISTANCE = 50;
	static constexpr int RANGE = 40;

	NewPing sonar1(TRIG1, ECHO1, MAX_DISTANCE);
	NewPing sonar2(TRIG2, ECHO2, MAX_DISTANCE);
	NewPing sonar3(TRIG3, ECHO3, MAX_DISTANCE);

	read(int);
}

#endif