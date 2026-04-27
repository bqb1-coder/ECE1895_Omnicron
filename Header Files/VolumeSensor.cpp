#include <Arduino.h>
#include "VolumeSensor.h"
#include "util.h"
#include "pin_config.h"


namespace VolumeSensor {
	static constexpr int NUM_SAMPLES = 750;

	int readVolume(int prevVolume)
	{
		int maxVal = 0;
		int minVal = 128;
		int aRead = 0;

		// Read in the samples to get the volume
		for (int i = 0; i < NUM_SAMPLES ; i++) {
			aRead = analogRead(MIC);
			maxVal = max(maxVal, aRead);
			minVal = min(minVal, aRead);
		}

		//Volume
		return maxVal - minVal;
	}

	int scaleVolume(int vol, float scalingFactor)
	{
		return round( pow(vol / 128.0, scalingFactor) * 128 );
	}

	int boundVolume(int volume)
	{
		volume = volume <= 0 ? 0 : volume;
		return volume > 128 ? 128 : volume;
	}
}