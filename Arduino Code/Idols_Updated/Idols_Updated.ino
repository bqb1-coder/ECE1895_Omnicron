#include <EEPROM.h>
#include "idols.h"
#include "game_functions.h"
#include "pin_config.h"

#define GAME_TIME 5000

//Reed switches and hall effect sensors


void setup() {
  //Use onboard EEPROM along with micros to generate a strong new seed every boot up 
  int rom0 = EEPROM.read(0);
  randomSeed(micros() * rom0);
  EEPROM.write(0, (rom0 + 1) % 256);

  pinMode(REED1, INPUT);
  pinMode(HALL1, INPUT);
  pinMode(REED2, INPUT);
  pinMode(HALL2, INPUT);
  pinMode(REED3, INPUT);
  pinMode(HALL3, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(RED3, OUTPUT);
  pinMode(BLUE3, OUTPUT);

  Serial.begin(9600);
}

/*

1. 
Pick colors for different positions
e.g.
- pos1 = RED
- pos2 = NONE
- pos3 = BLUE

2. 
bool matchReadings: function to determine if readings match a specific color
matches reed and hall effect readings to a certain color (red is fixed as north, blue as south)
e.g.
position1Correct = matchReadings(reed1, hall1, Color1)
position2Correct = matchReadings(reed2, hall2, Color2)
position3Correct = matchReadings(reed3, hall3, Color3)

3. 
allIdolsCorrect = position1Correct && position2Correct && position3Correct


*/


void loop() {
  Games::idolChallenge();
}

