int rand1;
int rand2;
int rand3;
int waitTime = 10000;
bool one_right = false;
bool two_right = false;
//defining sensor pins. Pole is the hall effect sensor. Presence is the reed switch
#define Presence1 A1
#define Pole1 A0
#define Presence2 A3
#define Pole2 A2
#define Presence3 A5
#define Pole3 A4

//defining LED1 pins
#define RED1 2
#define BLUE1 3
//
//defining LED2 pins
#define RED2 4
#define BLUE2 5

//defining LED3 pins
#define RED3 6
#define BLUE3 7

#define LED_PIN 2 //LED off when correct sequence

enum LEDColor {
  RED, 
  BLUE,
  NONE
}

void setup() {
  pinMode(LED_PIN, OUTPUT); //setting the led to output
  pinMode(Presence1, INPUT);
  pinMode(Pole1, INPUT);
  pinMode(Presence2, INPUT);
  pinMode(Pole2, INPUT);
  pinMode(Presence3, INPUT);
  pinMode(Pole3, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(RED3, OUTPUT);
  pinMode(BLUE3, OUTPUT);

  Serial.begin(9600);
  Serial.println("Board started!"); // test message

}

//
void loop() {
  one_right = false;
  two_right = false;
  generateNewNumbers();

  //rand1 the smallest var
  rand1 = 0;
  if (rand1 <= rand2 && rand1 <= rand3) { //
    //set LEDs to respective colors
    setAllLEDColors(RED, BLUE, NONE);

    delay(waitTime); //delay
    //user must place the Presence idol in LED1 spot
    //user must place Pole idol in LED2 spot

    Serial.println("starting idol check1");
    idolMatch(Presence1, Presence2, Pole1, Pole2); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol
  }
  //rand2 is the smallest var
  if (rand2 < rand1 && rand2 < rand3) {
    setAllLEDColors(BLUE, NONE, RED);

    delay(waitTime); //delay
    idolMatch(Presence3, Presence1, Pole3, Pole1); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol
  }
  //rand3 is the smallest var
  if (rand3 < rand1 && rand3 < rand2) {
    setAllLEDColors(NONE, RED, BLUE);
    delay(waitTime); //delay
    idolMatch(Presence2, Presence3, Pole2, Pole3); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol
  }
}

//edit the below function when integrating all actions.

// two idols, north facing and south facing
// hall effect sensor tests whether it is north or south facing
// north facing magnet makes HE go low

//presencePin is the reed switch. polePin is the hall effect sensor
//presencePin1 is the north facing idol presence
//presencePin2 is the south facing idol presence
void idolMatch(int presencePin1, int presencePin2, int polePin1, int polePin2) {

  if (digitalRead(presencePin1) == HIGH) { //if the idol in presencePin1's location is there
    if (digitalRead(polePin1) == LOW) { //if that idol is north facing - the red idol
      one_right = true; //correct choice
    }
  }
  if (digitalRead(presencePin2) == HIGH) {
    if (digitalRead(polePin2) == HIGH) { //if the south facing idol is there
      two_right = true;
    }
  }
  if (two_right && one_right) {
    digitalWrite(LED_PIN, LOW); //correct choices
    Serial.println("correct choice ");
    digitalWrite(BLUE1, HIGH);
    digitalWrite(BLUE2, HIGH);
    digitalWrite(BLUE3, HIGH);
    delay(waitTime / 50);
    digitalWrite(BLUE1, LOW);
    digitalWrite(BLUE2, LOW);
    digitalWrite(BLUE3, LOW);
    delay(waitTime / 50);
    digitalWrite(BLUE1, HIGH);
    digitalWrite(BLUE2, HIGH);
    digitalWrite(BLUE3, HIGH);
    delay(waitTime / 50);
    digitalWrite(BLUE1, LOW);
    digitalWrite(BLUE2, LOW);
    digitalWrite(BLUE3, LOW);
    delay(waitTime / 10);
    //return to start of the loop
    return;
  } else {
    Serial.println("incorrect choice ");
    digitalWrite(RED1, HIGH);
    digitalWrite(RED2, HIGH);
    digitalWrite(RED3, HIGH);
    delay(waitTime / 50);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    digitalWrite(RED3, LOW);
    delay(waitTime / 50);
    digitalWrite(RED1, HIGH);
    digitalWrite(RED2, HIGH);
    digitalWrite(RED3, HIGH);
    delay(waitTime / 50);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    digitalWrite(RED3, LOW);
    delay(waitTime / 10);
    //return to start of the loop
    return;
  }

}

void generateNewNumbers() {
  rand1 = random(1, 51);
  rand2 = random(1, 51);
  rand3 = random(1, 51);
}

void setLEDToColor(int LEDNum, LEDColor ledcolor)
{
  int redPin;
  int bluePin;

  switch (LEDNum) {
    case 1:
      redPin = RED1;
      bluePin = BLUE1;
    case 2:
      redPin = RED2;
      bluePin = BLUE2;
    case 3:
      redPin = RED3;
      bluePin = BLUE3;
  }

  int redLogicVal = ledcolor == RED ? HIGH : LOW;
  int blueLogicVal = ledcolor == BLUE ? HIGH : LOW;

  digitalWrite(redPin, redLogicVal);
  digitalWrite(bluePin, blueLogicVal);
}

void setAllLEDColors(LEDColor LED1, LEDColor LED2, LEDColor LED3)
{
  setLEDToColor(1, LED1);
  setLEDToColor(2, LED2);
  setLEDToColor(3, LED3);
}


