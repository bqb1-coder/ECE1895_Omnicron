  int rand1;
  int rand2;
  int rand3;
  int waitTime=10000;
  bool one_right=false;
  bool two_right=false;
  //defining sensor pins. Strong is the hall effect sensor. weak is the reed switch
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

  #define LED_PIN 2 //LED off when correct sequence
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
    
    delay(waitTime); //delay 

    //now checking the slots for the idols. the red hole corresponds to the stronger idol, the blue is weaker

    if(Weak3 == LOW){ //idol is in the third LED spot
      digitalWrite(LED_PIN, HIGH); //incorrect choice

      //return to start of the loop
      return;
    }
    if(Weak1 == HIGH || Weak2 == HIGH){ //idol is not in the first or second led location
      digitalWrite(LED_PIN, HIGH); //incorrect choice

      //return to start of the loop
      return;
    }
    if(Weak1 == LOW){ //if there is an idol in the first LEDs location
      if(Strong1 == HIGH){ //if that idol is the stronger idol
        one_right=true; //correct choice
      }else{ //if it is the weaker idol here
        digitalWrite(LED_PIN, HIGH); //incorrect choice

        //return to start of the loop
        return;
      }
    }
    if(Weak2 == LOW){
      if(Strong2 == HIGH){ //strong idol is placed in the second LED location
        digitalWrite(LED_PIN, HIGH); //incorrect choice

        //return to start of the loop
        return;
      }else{ //weak idol is in the second LED location
        two_right = true;
      }
    }
    if(two_right && one_right){
      digitalWrite(LED_PIN, LOW); //correct choices

        //return to start of the loop
        return;
    }

 }
 //rand2 is the smallest var
  if(rand2<rand1 && rand2<rand3){
      //set LED1 BLUE
        digitalWrite(RED1, LOW);
        digitalWrite(GREEN1, LOW);
        digitalWrite(BLUE1, HIGH);
      //set LED2 OFF
        digitalWrite(RED2, LOW);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, LOW);
      //set LED3 RED
        digitalWrite(RED2, HIGH);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, LOW);
    
    delay(waitTime); //delay


 }
 //rand3 is the smallest var
  if(rand3<rand1 && rand3<rand2){
      //set LED1 OFF
        digitalWrite(RED1, LOW);
        digitalWrite(GREEN1, LOW);
        digitalWrite(BLUE1, LOW);
      //set LED2 RED
        digitalWrite(RED2, HIGH);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, LOW);
      //set LED3 BLUE
        digitalWrite(RED2, LOW);
        digitalWrite(GREEN2, LOW);
        digitalWrite(BLUE2, HIGH);
    
    delay(waitTime); //delay 
 }
}
