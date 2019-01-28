#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "Serial.h"

#define VBATPIN 3
#define VCAPIN  2
#define IBATTPIN  1


void setup() 
{
  // put your setup code here, to run once:
  float vbatt=0;
  float vcap= 0;
  float ibatt = 0;
  float temp = 0;
  bool boost=false;
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int v_batt_raw =analogRead(VBATPIN);
  int v_cap_raw = analogRead(VCAPIN);
  int i_batt_raw = analogRead(IBATTPIN);

  vbatt = (5.0f / v_batt_raw) * VRATIO;
  vcap =(5.0f /v_cap_raw)*VRATIO;
  ibatt = (5.0f/i_batt_raw)*VRATIO;

  if(vcap <= VMIN)
  {
    boost =false;
  }
  if(vcap>=VBOOST)
  {
  boost = true; 
  }
  
  }
  lcd.print(vbatt);
  lcd.print(vcap);
  lcd.print(ibatt);
