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

#define ECHO1 A2
#define ECHO2 A1
#define ECHO3 A0

// KEYPAD CHALLENGE PINS
#define ROW1 5
#define ROW2 6
#define ROW3 7
#define ROW4 8

#define COL1 12
#define COL2 11
#define COL3 10 
#define COL4 9


/*
#################
	ATMEGA 2
#################
*/

// IDOL CHALLENGE PINS
#define REED1 9
#define HALL1 8
#define REED2 11
#define HALL2 10
#define REED3 13
#define HALL3 12

#define RED1  2
#define BLUE1 3
#define RED2  4
#define BLUE2 5
#define RED3  6
#define BLUE3 7

// AUDIO CHALLENGE PIN

#define MIC A0


#endif