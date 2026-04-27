#ifndef VOLUME_SENSOR_H
#define VOLUME_SENSOR_H

#include <Arduino.h>

namespace VolumeSensor {
	static constexpr float DEFAULT_SCALING_FACTOR = .55;
	const float ALPHA = .55;
  const float SCALING_POWER = .45;

	int readVolume();
	int scaleVolume(int vol, float scalingFactor = DEFAULT_SCALING_FACTOR);
	int boundVolume(int volume);
}

#endif