#include "OLED_2.h"
#include "error.h"
#include "game_functions.h"
#include "state_action.h"

#define WON_CHALLENGE 0xFF
#define LOST_CHALLENGE 0x55

#define INIT_COMMS  0xAA
#define CONTROLLER_ADDRESS 0x5E

#define CMD_BASE 0xC0
#define CMD_VOLUME_GAME (CMD_BASE + (int)Action::VOLUME)
#define CMD_IDOLS_GAME  (CMD_BASE + (int)Action::IDOLS)

volatile State currentState = State::WAITING;
volatile Action currentAction = Action::NONE;

Action actionTable[(int)Action::COUNT] = {
  Action::NONE,
  Action::VOLUME,
  Action::IDOLS
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), stopExecuting, FALLING);
  OLED2::begin();
  
  //Set input and output pins
  // for (int i = 0; i < numOutputPins; i++)
  //   pinMode(outputPins[i], OUTPUT);

  // for (int i = 0; i < numInputPins; i++)
  //   pinMode(inputPins[i], INPUT);

  /*
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
  */

  pinMode(REED1, INPUT);
  pinMode(HALL1, INPUT);
  pinMode(REED2, INPUT);
  pinMode(HALL2, INPUT);
  pinMode(REED3, INPUT);
  pinMode(HALL3, INPUT);
  pinMode(MIC, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(RED3, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(BLUE3, OUTPUT);
}

void loop() {
  interperetSerial();

  //Start the challenge and write result of game back to AT1
  if (currentState == State::EXEC)
  {
    // Serial.print(F("Action: "));
    // Serial.println((int)currentAction);
    bool wonChallenge = startChallenge();
    byte writeVal = LOST_CHALLENGE | (wonChallenge * WON_CHALLENGE);
    Serial.write(writeVal);
  }
}

bool startChallenge()
{
  bool wonChallenge = false;
  switch (currentAction)
  {
    case Action::IDOLS:
      wonChallenge = Games::idolChallenge(&currentState);
      break;
    case Action::VOLUME:
      wonChallenge = Games::volumeChallenge(&currentState);
  }
  return wonChallenge;
}

void updateCurrentState(byte reading)
{
  switch (currentState)
  {
    case State::WAITING:
      if (reading == INIT_COMMS) currentState = State::INIT;
      else currentState = State::WAITING;
      break;
    case State::INIT:
      if (reading == INIT_COMMS) currentState = State::VERIFY;
      else currentState = State::WAITING;
      break;
    case State::VERIFY:
      if (reading == CONTROLLER_ADDRESS) currentState = State::CMD;
      else if (reading == INIT_COMMS) currentState = State::INIT;
      else currentState = State::WAITING;
      break;
    case State::CMD:
      bool isCommand = (reading & 0xF0) == 0xC0;
      int index = (reading & 0xF);
      bool badIndex = (index < 0 || index >= (int)Action::COUNT);
      if (isCommand && badIndex)
        Error::raiseError(F(__FILE__),NULL,F("Bad command received"));
      if (isCommand)
      {
        currentState = State::EXEC;
        currentAction = actionTable[index];
      }
      else
        currentState = State::WAITING;
      break;
    case State::EXEC:
      // currentState = State::EXEC;
      break;
  }

}


void interperetSerial(){
  byte reading = 0;
  if (Serial.available() > 0)
  {
    reading = Serial.read();
    updateCurrentState(reading);
    // Serial.println(reading, HEX);
    // Serial.print("Current state: ");
    // Serial.println((int)currentState);
    // Serial.print("Current Action: ");
    // Serial.println((int)currentAction);
  }
}


void stopExecuting()
{
  currentState = State::WAITING;
  currentAction = Action::NONE;
}
