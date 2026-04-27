#include <SoftwareSerial.h>
#define rxPin 4
#define txPin 11

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // Begin serial and software serial
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    // Serial.println("[AT1] ");
    while (Serial.available() > 0) {
      Serial.print((char)Serial.read());
    }
  }

  if (mySerial.available() > 0) {
    // Serial.println("[AT2] ");
    while (mySerial.available() > 0) {
      Serial.print((char)mySerial.read());
    }
  }

}