  int rand1;
  int rand2;
  int rand3;
  int waitTime=5000;

  //defining sensor pins
  #define Strong1 36 
  #define Weak1 39
  #define Strong2 34 
  #define Weak2 35
  #define Strong3 32 
  #define Weak3 33

  //defining LED1 pins 
  #define RED1 25
  #define GREEN1 26 
  #define BLUE1 27

  //defining LED2 pins 
  #define RED2 23
  #define GREEN2 22
  #define BLUE2 21

  //defining LED2 pins 
  #define RED3 19
  #define GREEN3 18
  #define BLUE3 17

  #define LED_PIN 2 //LED on when correct sequence
void setup() {
  //making random numbers
  randomSeed(analogRead(0)); //need to make numbers random every boot
  rand1 = random(1,51); //generate a random number between 1 and 50
  rand2 = random(1,51); //generate a random number between 1 and 50
  rand3 = random(1,51); //generate a random number between 1 and 50

  pinMode(LED_PIN, OUTPUT); //setting the led to output
  pinMode(Strong1, INPUT);
  pinMode(Weak1, INPUT);

  

}

void loop() {
  //rand1 the smallest var
  if(rand1<=rand2 && rand1<=rand3){
      //set LED1 RED
        digitalWrite(RED1, HIGH);
        digitalWrite(GREEN1, LOW);
        digitalWrite(BLUE1, LOW);
      //set LED2 BLUE
        digitalWrite(RED2, LOW);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, HIGH);
      //set LED3 OFF
        digitalWrite(RED2, LOW);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, LOW);
    
    delay(waitTime); //delay 5 seconds 



  



//}


}
