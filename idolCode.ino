  // int rand1;
  // int rand2;
  // int rand3;
  // int waitTime=5000;
  #define B1 34 //will read in pin 13
  #define B2 35
  #define LED_PIN 2 //LED
void setup() {
  // //making random numbers
  // rand1 = random(1,50); //generate a random number between 1 and 50
  // rand2 = random(1,50); //generate a random number between 1 and 50
  // rand3 = random(1,50); //generate a random number between 1 and 50

  pinMode(LED_PIN, OUTPUT); //setting the led to output
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  //to do
  //find voltage values for LEDs corresponding to red, blue
  //figure out how LEDs work
  

}

void loop() {
  
  int stateA = digitalRead(B1);
  int stateB = digitalRead(B2);
  if(stateA == HIGH && stateB == HIGH){
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN,LOW);
  }


  // //rand1 the smallest var
  // if(rand1<=rand2 && rand1<=rand3){
  //     //set LED1 RED
  //     //set LED2 BLUE
  //     //set LED3 OFF
    
  //   delay(waitTime); //delay 5 seconds //will need to replace with a variable



  



//}


}
