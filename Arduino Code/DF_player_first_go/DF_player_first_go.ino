#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00

#define INIT 0x3F
#define SET_PLAYBACK_MODE 0x08
#define SET_TRACK_NUM 0x03
#define PLAYBACK 0x0D
#define NEXT_TRACK 0x01
#define SET_EQ 0x07
#define REPEAT 0x11
#define PAUSE 0xE

#define EQ_NORMAL 0x0

#define RPT_NO_REPEAT 0x0
#define PBMODE_REPEAT 0x0
// #define 
/*
void setup() {
  Serial.begin(9600);
  delay(5000);

  execute_CMD(INIT, 0);  // init
  setVolume(30);
  // execute_CMD(SET_PLAYBACK_MODE, PBMODE_REPEAT);
  execute_CMD(SET_EQ, EQ_NORMAL); 
  // execute_CMD(REPEAT, RPT_NO_REPEAT);

  // Serial.println();
  // Serial.println("Playing track 0");

  execute_CMD(SET_TRACK_NUM, 1);
  execute_CMD(PLAYBACK, 0);

  delay(5000);

  // Serial.println("Pausing track");
  execute_CMD(PAUSE, 0);

  while(1);

  for (int i = 1; i <= 5; i++)
  {
    // Serial.print("Track: ");
    // Serial.println(i);
    execute_CMD(SET_TRACK_NUM, i);
    execute_CMD(PLAYBACK, 0);
    delay(5000);
  }
  
}
// */

// 1 - Lose music
// 2 - Indiana Jones
// 3 - Chant it
// 4 - Hack it
// 5 - Offer it
enum Track  {
  LOSE=1,
  INDIE,
  CHANT,
  HACK,
  OFFER
};


void setup() {
  Serial.begin(9600);

  execute_CMD(INIT,0, 0);
  delay(1500);

  setVolume(20);
  // execute_CMD(SET_EQ, EQ_NORMAL);
  // ← no REPEAT command here; just let tracks play normally

  execute_CMD(SET_TRACK_NUM, 0, INDIE);

  delay(5000);

  execute_CMD(PAUSE, 0, 0);

  delay(2500);

  execute_CMD(SET_TRACK_NUM, 0, LOSE);





  while(1);

  for (int i = 1; i <= 5; i++) {
    execute_CMD(SET_TRACK_NUM, 0,  i);
    execute_CMD(PLAYBACK, 0, 0);
    delay(5000);
    execute_CMD(PAUSE, 0, 0);
    delay(500);
  }
}


void loop() {
  // nothing needed — module loops tracks automatically
}

void execute_CMD(byte CMD, byte Par1, byte Par2) {
  // byte Par1 = (param >> 8) & 0xFF;
  // byte Par2 = (param) & 0xFF;

  // Serial.println();
  // Serial.println(CMD, HEX);
  // Serial.println(Par1, HEX);
  // Serial.println(Par2, HEX);

  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

  byte Command_line[10] = {
    Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
    Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
  };

  for (byte k = 0; k < 10; k++) {
    Serial.write(Command_line[k]);
  }
  delay(50);
}

void setVolume(int volume) 
{
  execute_CMD(0x06, 0, volume);
  delay(500);
}