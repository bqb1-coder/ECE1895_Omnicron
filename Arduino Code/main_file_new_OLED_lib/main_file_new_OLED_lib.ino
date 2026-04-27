#include <Wire.h>
#include "game_functions.h"
#include "OLED_1.h"
// #include "OLED_2.h"
#include "util.h"
#include "keypad.h"
#include "lcd.h"
#include "pin_config.h"
#include "error.h"
#include "timer.h"
#include "UARTx.h"
#include "timer.h"
#include "Audio.h"
#include <EEPROM.h>


#define WIN_SCORE 99
#define KEYPAD_KEYS 2
#define TIMER_INT_PIN 2
#define HIGH_SCORE_MEM_ADDRESS 0x10
#define TIMER_DEC_VALUE .025

int playerScore = 0;
int highScore = 0;
int timerValue = 5000;

void setup() {
  //Configure pin modes
  //Set input and output pins
  Serial.begin(9600);
  Wire.begin();

  // for (int i = 0; i < numOutputPins; i++)
  //   pinMode(outputPins[i], OUTPUT);

  // for (int i = 0; i < numInputPins; i++)
  //   pinMode(inputPins[i], INPUT);

  pinMode(INTERRUPT_PERIPHERAL, OUTPUT);

  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(ROW4, OUTPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(TRIG3, OUTPUT);

  pinMode(COL1, INPUT);
  pinMode(COL2, INPUT);
  pinMode(COL3, INPUT);
  pinMode(COL4, INPUT);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(ECHO3, INPUT);

  //Initializations

  if (EEPROM.read(HIGH_SCORE_MEM_ADDRESS) == 255)
  {
    EEPROM.write(HIGH_SCORE_MEM_ADDRESS, 0);
  }

  Audio::init();
  Audio::setVolume(25);
  LCD::begin();
  Keypad::configureKeypadPins();
  OLED1::begin();
  Timer::begin(TIMER_INT_PIN, FALLING);
  bool RTC_configured = Timer::isConfigured();

  OLED1::printCenteredString("bingus"); // bingus

  if (!RTC_configured)
    Error::raiseError(F(__FILE__), NULL, F("RTC not configured"));

  LCD::displayWelcome();

}

void beginGame()
{
  bool nextRound = true;
  bool wonChallenge = false;
  
  while(nextRound)
  {
    wonChallenge = gameBody();

    if (wonChallenge) 
      Audio::playTrack(Track::WHIP); //Play the audio for end of a challenge based on win/lose
    
    delay(1500);

    playerScore += (wonChallenge * 1); // Increase by one if user won challenge
    nextRound = wonChallenge && (playerScore < WIN_SCORE); // Advance if player won and did not reach max score
    timerValue -= TIMER_DEC_VALUE;
    LCD::printScore(playerScore);
  }

}


bool gameBody()
{
  Challenge chall = Util::chooseChallenge(); 
  bool wonChallenge = false;
  // float surpriseChance = Util::determineChance(playerScore); 
  bool surpriseActive = false; //Util::activateSurprise(surpriseChance); 

  Timer::startTimer(timerValue);

  switch (chall)
  {
    case KEYPAD:
      Audio::playTrack(Track::HACK);
      wonChallenge = Games::keypadChallenge(KEYPAD_KEYS);
      // Audio::pause();
      break;
    case IDOLS:
      Audio::playTrack(Track::OFFER);
      wonChallenge = Games::idolChallenge();
      // Audio::pause();
      break;
    case AUDIO:
      Audio::playTrack(Track::CHANT);
      wonChallenge = Games::volumeChallenge();
      // Audio::pause();
      break;
  }

  return wonChallenge;

  // if (!wonChallenge) return false;

  // if (surpriseActive)
  // {
  //   //Audio::playTrack("Surprise");
  //   wonChallenge = Games::avoidChallenge();
  // }

  // return wonChallenge;
}


void loop() {
  //Await the keypad to be pressed to being game
  LCD::awaitKeypad();
  Keypad::awaitGameStart();
  Audio::pause();  
  LCD::clear();
  delay(1000);

  //Set the randomness seed 
  randomSeed(micros() * Util::updateEEPROM());

  //Begin the game
  beginGame();

  delay(500);
  
  if(playerScore == WIN_SCORE)
    Audio::playTrack(Track::INDIE);
  else
    Audio::playTrack(Track::LOSE);

  //Display game over
  LCD::gameOver(playerScore, WIN_SCORE);

  delay(3000);

  highScore = EEPROM.read(HIGH_SCORE_MEM_ADDRESS);
  if (playerScore > highScore) {
    highScore = playerScore;
    LCD::highScore(highScore);
    delay(3000);
    EEPROM.write(HIGH_SCORE_MEM_ADDRESS, highScore);
  }

  playerScore = 0;
}
