#include "Arduino.h"
#include <LTC4622G.h>

LTC4622G myDisplay = LTC4622G();

void setup() {
  // put your setup code here, to run once:
}

unsigned long lastChanged=0;
int value=0;
float vout=0.0;

void loop() {
  unsigned long now = millis();
  
  // Keep the display uptodate
  myDisplay.update();

  // read ADC
  value = analogRead(A0);
  // Calculate
  vout = (value * 5.0) / 1024.0; // see text
  
  // Change not too fast
  if ( now - lastChanged > 200 ) {
    myDisplay.setValue(vout);
    lastChanged = now;
  }
  
}
