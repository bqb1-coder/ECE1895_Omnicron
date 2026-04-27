#include "UARTx.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  UARTx::sendCommand(UARTx::CMD_IDOLS_GAME);
  delay(2500);
  digitalWrite(13, LOW);
  bool won = UARTx::awaitResponse();
  Serial.print(won);
}

void loop() {
  // put your main code here, to run repeatedly:

}
