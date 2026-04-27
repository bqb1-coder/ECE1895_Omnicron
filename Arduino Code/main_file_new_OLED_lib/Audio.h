#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>
#include <stdint.h>

enum Track {
	LOSE=1,
	INDIE,
	CHANT,
	HACK,
	OFFER,
	WHIP
};

namespace Audio
{
	#define Start_Byte 0x7E
	#define Version_Byte 0xFF
	#define Command_Length 0x06
	#define End_Byte 0xEF
	#define Acknowledge 0x00

	#define INIT 0x3F
	#define SET_TRACK_NUM 0x03
	#define PAUSE 0xE

	void init();
	void playTrack(Track track);
	void executeCMD(byte, byte, byte);
	void setVolume(int);
	void pause();
}

#endif