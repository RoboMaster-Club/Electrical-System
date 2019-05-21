#include <Wire.h>
#include "Adafruit_MCP23008.h"

/**
 * Testing digital pins control for pneumatic system
 **/

Adafruit_MCP23008 pneumatic;
  
void setup() {  
  pneumatic.begin();      // use default address 0x20

  // The first 4 pins of the MCP23008 are used for control
  pneumatic.pinMode(0, OUTPUT);
  pneumatic.pinMode(1, OUTPUT);
  pneumatic.pinMode(2, OUTPUT);
  pneumatic.pinMode(3, OUTPUT);

  for(int i = 0; i < 4; i++)
  {
    // Set high for all pins
    pneumatic.digitalWrite(i, HIGH);
  }
  
}


// flip the pin #0 up and down

void loop() {
  // Alternating

  delay(1000);

  for(int i = 0; i < 4; i++)
  {
    pneumatic.digitalWrite(i, LOW);
  }

  delay(1000);

  for(int i = 0; i < 4; i++)
  {
    // Set high for all pins
    pneumatic.digitalWrite(i, HIGH);
  }
}