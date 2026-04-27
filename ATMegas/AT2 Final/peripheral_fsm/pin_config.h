#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#define A0 14
#define A1 15


/*
#################
	ATMEGA 2
#################
*/

// IDOL CHALLENGE PINS
#define REED1 10
#define HALL1 9
#define REED2 12
#define HALL2 11
#define REED3 14
#define HALL3 13

#define RED1  3
#define BLUE1 4
#define RED2  5
#define BLUE2 6
#define RED3  7
#define BLUE3 8

// AUDIO CHALLENGE PIN

#define MIC A1

#define numOutputPins 6
#define numInputPins  7
static constexpr int outputPins[numOutputPins] = {
	RED1,
	RED2,
	RED3,
	BLUE1,
	BLUE2,
	BLUE3
};

static constexpr int inputPins[numInputPins] = {
	REED1,
	REED2,
	REED3,
	HALL1,
	HALL2,
	HALL3,
	MIC
};

#endif