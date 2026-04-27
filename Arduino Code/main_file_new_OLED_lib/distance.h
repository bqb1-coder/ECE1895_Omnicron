#ifndef DISTANCE_H
#define DISTANCE_H

#include <Arduino.h>
#include <NewPing.h>
#include "pin_config.h"

namespace Distance
{
	static constexpr int MAX_DISTANCE = 50;
	static constexpr int RANGE = 40;

	int read(int);
}

#endif