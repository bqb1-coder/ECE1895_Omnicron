#include "pin_config.h"
#include <avr/pgmspace.h>

const int outputPins [numOutputPins] PROGMEM = {
	TRIG1,
	TRIG2,
	TRIG3, 
	ROW1,
	ROW2,
	ROW3,
	ROW4, 
	INTERRUPT_PERIPHERAL
};

const int inputPins[numInputPins] PROGMEM = {
	ECHO1,
	ECHO2,
	ECHO3,
	COL1,
	COL2,
	COL3,
	COL4
};
