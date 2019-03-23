#include <Wire.h>
//#include "Adafruit_MCP9808.h"
//#include "Serial.h"

# define VBATPIN A0
# define VCAPIN  A1
# define IBATTPIN  A2
# define VRATIO 30.0//votage ratio: max voltage displayed
# define VMIN 1
# define VBOOST A3

float vbatt = 0; //votage of battery
float vcap = 0; //votage of capacitor
float ibatt = 0; //current of battery
float temp = 0;
bool boost = false; //whether it boosts

//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  tempsensor.setResolution(3);

  //Voltage Regulator
  pinMode(VBATPIN, INPUT);
  pinMode(VCAPIN, INPUT);
  pinMode(IBATTPIN, INPUT);
}

void loop() {
  // temp sensor
  tempsensor.wake();
  float c = tempsensor.readTempC();
  float f = tempsensor.readTempF();

  delay(2000);

  //reading data from mainboard
  float v_batt_raw = analogRead(VBATPIN); //A6
  float v_cap_raw = analogRead(VCAPIN); //A9
  float i_batt_raw = analogRead(IBATTPIN); //A10

  vbatt = (v_batt_raw / 1023) * VRATIO;     //Hey we're getting 1.5ish when we're supposed to get 4.23 and we don't know why. Fantastic.
  vcap =(v_cap_raw / 1023) * VRATIO;
  ibatt = (i_batt_raw / 1023) * VRATIO;

  if(vcap <= VMIN)
  {
    boost =false;
  }
  if(vcap>=VBOOST)
  {
    boost = true; 
  }

  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
  delay(200);


  //send data to rasp pi
  Serial.print("VCap = ");
  Serial.println(vcap);
  Serial.print("Boost = ");
  Serial.println(boost);
  Serial.print("Temp: "); 
  Serial.print(c, 4); Serial.print("*C\t and "); 
  Serial.print(f, 4); Serial.println("*F.");
  delay(2000);
}
