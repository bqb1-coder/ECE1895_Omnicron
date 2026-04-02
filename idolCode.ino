  int rand1;
  int rand2;
  int rand3;
  int waitTime=10000;
  bool one_right=false;
  bool two_right=false;
  //defining sensor pins. Pole is the hall effect sensor. Presence is the reed switch
  #define Presence1 A1
  #define Pole1 A0
  #define Presence2 A3
  #define Pole2 A2
  #define Presence3 A5
  #define Pole3 A4

  //defining LED1 pins 
  #define RED1 28
  #define BLUE1 3
//
  //defining LED2 pins 
  #define RED2 4
  #define BLUE2 5

  //defining LED3 pins 
  #define RED3 6
  #define BLUE3 7

  #define LED_PIN 2 //LED off when correct sequence
void setup() {
  //making random numbers

  pinMode(LED_PIN, OUTPUT); //setting the led to output
  pinMode(Presence1, INPUT);
  pinMode(Pole1, INPUT);
  pinMode(Presence2, INPUT);
  pinMode(Pole2, INPUT);
  pinMode(Presence3, INPUT);
  pinMode(Pole3, INPUT);
  Serial.begin(921600);
  Serial.println("Board started!");  // test message
  pinMode(RED1, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(RED3, OUTPUT);
  pinMode(BLUE3, OUTPUT);

}

//
void loop() {
  one_right=false;
  two_right=false;
  generateNewNumbers();
  Serial.println("rand1 is: ");
  Serial.println(rand1);
  Serial.println("rand2 is: ");
  Serial.println(rand2);
  Serial.println("rand3 is: ");
  Serial.println(rand3);
  
  //rand1 the smallest var
  rand1=0;
  if(rand1<=rand2 && rand1<=rand3){
      //set LED1 RED
        digitalWrite(RED1, HIGH);
        digitalWrite(BLUE1, LOW);
      //set LED2 BLUE
        digitalWrite(RED2, LOW);
        digitalWrite(BLUE2, HIGH);
      //set LED3 OFF
        digitalWrite(RED3, LOW);
        digitalWrite(BLUE3, LOW);
    
    delay(waitTime); //delay 
    //user must place the Presence idol in LED1 spot
    //user must place Pole idol in LED2 spot

    Serial.println("starting idol check1");
    idolMatch(Presence1,Presence2,Pole1,Pole2); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol
    }
     //rand2 is the smallest var
  if(rand2<rand1 && rand2<rand3){
      //set LED1 BLUE
        digitalWrite(RED1, LOW);
        digitalWrite(BLUE1, HIGH);
      //set LED2 OFF
        digitalWrite(RED2, LOW);
        digitalWrite(BLUE2, LOW);
      //set LED3 RED
        digitalWrite(RED3, HIGH);
        digitalWrite(BLUE3, LOW);
    
    delay(waitTime); //delay
    idolMatch(Presence3,Presence1,Pole3,Pole1); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol
  }
     //rand3 is the smallest var
  if(rand3<rand1 && rand3<rand2){
      //set LED1 OFF
        digitalWrite(RED1, LOW);
        digitalWrite(BLUE1, LOW);
      //set LED2 RED
        digitalWrite(RED2, HIGH);
        digitalWrite(BLUE2, LOW);
      //set LED3 BLUE
        digitalWrite(RED3, LOW);
        digitalWrite(BLUE3, HIGH);
    
    delay(waitTime); //delay 
    idolMatch(Presence2,Presence3,Pole2,Pole3); //first two inputs are where the idol should be. third input is where the Presenceer idol should be. fourth is Pole idol

}
}



//edit the below function when integrating all actions.

// two idols, north facing and south facing
// hall effect sensor tests whether it is north or south facing
// north facing magnet makes HE go low

//presencePin is the reed switch. polePin is the hall effect sensor
//presencePin1 is the north facing idol presence
//presencePin2 is the south facing idol presence
void idolMatch(int presencePin1, int presencePin2, int polePin1, int polePin2){

    if(digitalRead(presencePin1) == HIGH){ //if the idol in presencePin1's location is there
      if(digitalRead(polePin1) == LOW){ //if that idol is north facing - the red idol
        one_right=true; //correct choice
      }
    }
    if(digitalRead(presencePin2) == HIGH){
      if(digitalRead(polePin2) == HIGH){ //if the south facing idol is there
          two_right = true;
      }
    }
    if(two_right && one_right){
      digitalWrite(LED_PIN, LOW); //correct choices
      Serial.println("correct choice ");
      digitalWrite(BLUE1,HIGH);
      digitalWrite(BLUE2,HIGH);
      digitalWrite(BLUE3,HIGH);
      delay(waitTime/50);
      digitalWrite(BLUE1,LOW);
      digitalWrite(BLUE2,LOW);
      digitalWrite(BLUE3,LOW);
      delay(waitTime/50);
      digitalWrite(BLUE1,HIGH);
      digitalWrite(BLUE2,HIGH);
      digitalWrite(BLUE3,HIGH);
      delay(waitTime/50);
      digitalWrite(BLUE1,LOW);
      digitalWrite(BLUE2,LOW);
      digitalWrite(BLUE3,LOW);
      delay(waitTime/10);
        //return to start of the loop
        return;
    }else{
      Serial.println("incorrect choice ");
      digitalWrite(RED1,HIGH);
      digitalWrite(RED2,HIGH);
      digitalWrite(RED3,HIGH);
      delay(waitTime/50);
      digitalWrite(RED1,LOW);
      digitalWrite(RED2,LOW);
      digitalWrite(RED3,LOW);
      delay(waitTime/50);
      digitalWrite(RED1,HIGH);
      digitalWrite(RED2,HIGH);
      digitalWrite(RED3,HIGH);
      delay(waitTime/50);
      digitalWrite(RED1,LOW);
      digitalWrite(RED2,LOW);
      digitalWrite(RED3,LOW);
      delay(waitTime/10);
        //return to start of the loop
        return;      
    }


 }
void generateNewNumbers() {
  rand1 = random(1, 51);
  rand2 = random(1, 51);
  rand3 = random(1, 51);
}






