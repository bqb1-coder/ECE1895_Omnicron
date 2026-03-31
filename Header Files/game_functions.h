bool keypadChallenge(int stringLength, int maxTime = 5000)
{
  char pressedChar = '-';

  int startTime = 0;
  int currentTime = 0;

  char displayString[stringLength+1];
  char randomString[stringLength+1];

  int numCorrect = 0;

  

  //Pick a new random string of characters
  pickRandomString(randomString, stringLength);
  strcpy(displayString, randomString);


  numCorrect = 0;

  // Write current string to screen
  display.clearDisplay();
  printCenteredString(displayString, stringLength);
  display.display();


  //Enter the challenge
  while (1)
  {
    //Check the timer, end if over time
    if (RTCTimerExpired())
    {
      return false;
    }
    
    pressedChar = '-'; // reset to random character each iteration

    //Check if a character has come in on serial line and read it if so
    if (Serial.available() > 0)
    {
      pressedChar = Serial.read();
    }

    // If no key pressed (at default value) just continue to next iteration
    if (pressedChar == '-')
      continue;

    // If they get the key correct 
    if (pressedChar == randomString[numCorrect])
    {
      displayString[numCorrect] = ' ';
      numCorrect++;
    }
    else //If not, return false;
    {
      return false;
    }

    // Write current string to screen
    display.clearDisplay();
    printCenteredString(displayString, stringLength);
    display.display();

    //When they get all correct, loop back around and go again
    if (numCorrect == stringLength)
      return true;
  }
}