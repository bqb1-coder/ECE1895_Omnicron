#ifndef VOLUME_SENSOR_H
#define VOLUME_SENSOR_H

#include <Arduino.h>

namespace VolumeSensor {
	static constexpr float DEFAULT_SCALING_FACTOR = .55;

	int readVolume(int prevVolume);
	int scaleVolume(int vol, float scalingFactor = DEFAULT_SCALING_FACTOR);
	int boundVolume(int volume);
}

#endif