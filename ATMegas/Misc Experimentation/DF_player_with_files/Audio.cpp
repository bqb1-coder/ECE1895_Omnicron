#include "Audio.h"
#include <Arduino.h>
#include <stdint.h>

namespace Audio
{
	void init()
	{
		executeCMD(INIT,0, 0);
		delay(1500);
	}

	void playTrack(Track track)
	{
		executeCMD(SET_TRACK_NUM, 0, track);
	}

	void pause()
	{
		executeCMD(PAUSE, 0, 0);
	}

	void executeCMD(byte CMD, byte Par1, byte Par2)
	{
		word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

		byte Command_line[10] = {
			Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
			Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
		};

		for (byte k = 0; k < 10; k++) {
			Serial.write(Command_line[k]);
		}
		delay(50);
	}

	void setVolume(int volume)
	{
		executeCMD(0x06, 0, volume);
  	delay(500);
	}
}