#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
//#include "Serial.h"

# define VBATPIN 6
# define VCAPIN  9
# define IBATTPIN  10
# define VRATIO 30 //Votage ratio: max voltage displayed
# define VMIN 1
# define VBOOST 10

Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float vbatt = 0; //votage of battery
float vcap = 0; //votage of capacitor
float ibatt = 0; //current of battery
float temp = 0;
bool boost = false; //whether it boosts

void setup() 
{
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);

  pinMode(VBATPIN, INPUT);
  pinMode(VCAPIN, INPUT);
  pinMode(IBATTPIN, INPUT);
}

void loop() 
{
  //reading data from mainboard
  int v_batt_raw = analogRead(VBATPIN);
  int v_cap_raw = analogRead(VCAPIN);
  int i_batt_raw = analogRead(IBATTPIN);

  vbatt = (float(v_batt_raw) / 1023) * VRATIO;
  vcap =(float(v_cap_raw) / 1023) * VRATIO;
  ibatt = (float(i_batt_raw) / 1023) * VRATIO;

  if(vcap <= VMIN)
  {
    boost =false;
  }
  if(vcap>=VBOOST)
  {
    boost = true; 
  }
  
  lcd.setCursor(0, 0);
  lcd.print("vb:");
  lcd.print(vbatt);
  lcd.print(" vc:");
  lcd.print(vcap);
  lcd.setCursor(0, 1);
  lcd.print("ib:");
  lcd.print(ibatt);
  }
