#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C

// Example code for HW484 v0.2: Reading an analog sensor
#define NUM_SAMPLES 800
#define ALPHA .5


int prevVolume = 0;
int volume = 0;
int maximumVolumeReached = 0;

int leftBound = 35; //random(10, 65);
int rightBound = 92; //random(78, 118);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(true); // Don't proceed, loop forever
  }

  randomSeed(analogRead(A1));

  // display.clearDisplay();
  // display.fillRect(leftBound, 56, rightBound - leftBound, 8, WHITE);
  // display.display();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int maxVal = 0;
  int minVal = 1024;
  int aRead = 0;
  
  // prevVolume = volume;

  for (int i = 0; i < NUM_SAMPLES ; i++) {
    aRead = analogRead(A0);
    maxVal = max(maxVal, aRead);
    minVal = min(minVal, aRead);
  }

  volume = maxVal - minVal;
  prevVolume = lowPassFilter(volume, prevVolume, ALPHA);

  int boundedVol = prevVolume > 128 ? 128 : prevVolume;
  display.clearDisplay();
  display.fillCircle(boundedVol, 40, 5, WHITE);
  display.fillRect(leftBound, 56, rightBound - leftBound, 8, WHITE);
  display.display();

}

float lowPassFilter(float X, float Y, float a)
{
  return X + a * (Y - X); //EWMA Filter formula
}