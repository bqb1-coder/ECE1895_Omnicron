#include "OLED_2.h"


void setup() {
  // put your setup code here, to run once:
  OLED2::begin();  
  OLED2::drawTargetBox(25, 60);
}

int counter = 0;

int aRead = 0;
int maxVal = 0;
int minVal = 1024;

void loop() {

  for (int i = 0; i < 650 ; i++) {
			aRead = analogRead(A0);
			maxVal = max(maxVal, aRead);
			minVal = min(minVal, aRead);
	}

  // OLED2::clearVolumeLevel(60);
  OLED2::showVolumeLevel(60);

}
