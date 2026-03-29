// Example code for HW484 v0.2: Reading an analog sensor
#define NUM_SAMPLES 800
#define ALPHA .5


void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

int prevVolume = 0;
int volume = 0;
int maximumVolumeReached = 0;

void loop() {

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
  maximumVolumeReached = max(volume, maximumVolumeReached);
  // Serial.println(prevVolume);     // Print the sensor value to the Serial Monitor
  Serial.println(maximumVolumeReached);
}

float lowPassFilter(float X, float Y, float a)
{
  return X + a * (Y - X); //EWMA Filter formula
}
