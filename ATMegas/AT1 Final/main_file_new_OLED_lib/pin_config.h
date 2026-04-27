#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

/*
#################
	ATMEGA 1
#################
*/

// SURPRISE CHALLENGE PINS
#define TRIG1 13
#define TRIG2 3
#define TRIG3 4

#define ECHO1 A0
#define ECHO2 A1
#define ECHO3 A2

// KEYPAD CHALLENGE PINS
#define ROW1 5
#define ROW2 6
#define ROW3 7
#define ROW4 8

#define COL1 12
#define COL2 11
#define COL3 10 
#define COL4 9

#define INTERRUPT_PERIPHERAL A3

#define numOutputPins 8
#define numInputPins  7

extern const int outputPins[numOutputPins];
extern const int inputPins[numInputPins];

#endif