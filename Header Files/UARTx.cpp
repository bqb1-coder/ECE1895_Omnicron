#include "UARTx.h"
#include <Arduino.h>
#include "error.h"

namespace UARTx 
{
	void sendCommand(uint8_t CMD)
	{
		int delTime = 25;
		Serial.write(INIT_COMMS);
		delay(delTime);
		Serial.write(INIT_COMMS);
		delay(delTime);
		Serial.write(CONTROLLER_ADDRESS);
		delay(delTime);
		Serial.write(CMD);
	}

	bool awaitResponse()
	{
		while (Serial.available() < 0);
		int readVal = Serial.read();
		switch (readVal) {
			case WON_CHALLENGE:
				return true;
			case LOST_CHALLENGE:
				return false;
			default:
				Error::raiseError(__FILE__, __func__, F"Bad response on Serial line") ;
		}
	}
}