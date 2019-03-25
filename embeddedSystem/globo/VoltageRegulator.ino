# define VBATPIN A0
# define VCAPIN  A1
# define IBATTPIN  A2
# define VRATIO 30.0//votage ratio: max voltage displayed
# define VMIN 1
# define VBOOST A3

Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float vbatt = 0; //votage of battery
float vcap = 0; //votage of capacitor
float ibatt = 0; //current of battery
float temp = 0;
bool boost = false; //whether it boosts

void setup2() 
{
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  pinMode(VBATPIN, INPUT);
  pinMode(VCAPIN, INPUT);
  pinMode(IBATTPIN, INPUT);
}

void loop2() 
{
  //reading data from mainboard
  float v_batt_raw = analogRead(VBATPIN); //A6
  float v_cap_raw = analogRead(VCAPIN); //A9
  float i_batt_raw = analogRead(IBATTPIN); //A10

  //Serial.println(v_batt_raw);
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
  
  lcd.setCursor(0, 0);
  lcd.print("vb:");
  lcd.print(vbatt);
  lcd.print(" vc:");
  lcd.print(vcap);
  lcd.setCursor(0, 1);
  lcd.print("ib:");
  lcd.print(ibatt);
  }
