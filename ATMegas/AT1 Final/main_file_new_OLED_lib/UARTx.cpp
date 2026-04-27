#include "UARTx.h"
#include <Arduino.h>
#include "error.h"
#include "timer.h"
#include "pin_config.h"

namespace UARTx 
{
	void sendCommand(uint8_t CMD)
	{
		int delTime = 15;
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
		digitalWrite(INTERRUPT_PERIPHERAL, HIGH);
		while (!Timer::isTimerExpired());
		digitalWrite(INTERRUPT_PERIPHERAL, LOW);
		while (Serial.available() <= 0);
		int readVal = Serial.read();
		switch (readVal) {
			case WON_CHALLENGE:
				return true;
			case LOST_CHALLENGE:
				return false;
			default:
				Error::raiseError(F(__FILE__), NULL, F("Bad response on Serial line")) ;
		}
	}
}