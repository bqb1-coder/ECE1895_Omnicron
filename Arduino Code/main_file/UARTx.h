#ifndef UART_COMMS_H
#define UART_COMMS_H

#include <Arduino.h>
#include <stdint.h>

namespace UARTx {

	static constexpr byte WON_CHALLENGE = 0xFF;
	static constexpr byte LOST_CHALLENGE = 0x55;

	static constexpr byte INIT_COMMS = 0xAA;
	static constexpr byte CONTROLLER_ADDRESS = 0x5E;

	static constexpr byte CMD_BASE = 0xC0;
	static constexpr byte CMD_VOLUME_GAME = (CMD_BASE + 0x1);
	static constexpr byte CMD_IDOLS_GAME = (CMD_BASE + 0x2);

	void sendCommand(uint8_t CMD);
	bool awaitResponse();

}

#endif