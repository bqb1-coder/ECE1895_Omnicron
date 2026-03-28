#include <NewPing.h>

#define TRIG_PIN 25
#define ECHO_PIN 26
#define MAX_DISTANCE 1000 //10 meters
#define LED_PIN 2
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(921600);
}

void loop() {
  delay(500);
  Serial.print("Distance: ");
  unsigned int cms=sonar.ping_cm();
  Serial.print(sonar.ping_cm());
  Serial.println(" cm");
  if(cms>1*100){ //within a meter
    digitalWrite(LED_PIN,HIGH);
  }
}