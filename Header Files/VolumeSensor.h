#ifndef VOLUME_SENSOR_H
#define VOLUME_SENSOR_H

namespace VolumeSensor {
	static constexpr int SENSOR_PIN = 14; // A0
	static constexpr int DEFAULT_SCALING_FACTOR = .55;

	int readVolume(int prevVolume);
	int scaleVolume(int vol, float scalingFactor = DEFAULT_SCALING_FACTOR);
	int boundVolume(int volume);
}

#endif