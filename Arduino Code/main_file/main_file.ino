#include "game_functions.h"
#include "OLED_1.h"
#include "util.h"
#include "keypad.h"
#include "lcd.h"
#include "pin_config.h"
#include "error.h"
#include "timer.h"
#include "UARTx.h"
#include "timer.h"


#define WIN_SCORE 99
#define KEYPAD_KEYS 3

int playerScore = 0;

void setup() {
  //Configure pin modes
  //Set input and output pins
  Serial.begin(9600);
  
  Serial.println(F(" I am alive"));
  LCD::begin();
  Serial.println(F("Displaying welcome"));
  LCD::displayWelcome();
  Serial.println(F("Displayed welcome"));
  Keypad::awaitGameStart();

  for (int i = 0; i < numOutputPins; i++)
    pinMode(outputPins[i], OUTPUT);

  for (int i = 0; i < numInputPins; i++)
    pinMode(inputPins[i], INPUT);

  //Initializations
  OLED1::begin();
  Timer::begin(2, FALLING);

  //Display the welcome to the user and await keypad press
  

  randomSeed(micros() * Util::updateEEPROM());

  beginGame();
}

void beginGame()
{
  bool nextRound = true;
  bool wonChallenge = false;
  
  while(nextRound)
  {
    wonChallenge = gameBody();
    //Audio::playAudio("Challenge End", wonChallenge); //Play the audio for end of a challenge based on win/lose
    playerScore += (wonChallenge * 1); // Increase by one if user won challenge
    nextRound = wonChallenge && (playerScore < WIN_SCORE); // Advance if player won and did not reach max score
  }

  LCD::gameOver(playerScore, WIN_SCORE);
}


bool gameBody()
{
  Challenge chall = Util::chooseChallenge();
  bool wonChallenge = false;
  float surpriseChance = Util::determineChance(playerScore);
  bool surpriseActive = Util::activateSurprise(surpriseChance);

  Timer::startTimer(5000);

  switch (chall)
  {
    case KEYPAD:
      //Audio::playAudio("Keypad");
      wonChallenge = Games::keypadChallenge(KEYPAD_KEYS);
      break;
    case IDOLS:
      //Audio::playAudio("Idols");
      wonChallenge = Games::idolChallenge();
      break;
    case AUDIO:
      //Audio::playAudio("Volume");
      wonChallenge = Games::volumeChallenge();
      break;
  }

  if (!wonChallenge) return false;

  if (surpriseActive)
  {
    //Audio::playAudio("Surprise");
    wonChallenge = Games::avoidChallenge();
  }

  return wonChallenge;
}


void loop() {}
