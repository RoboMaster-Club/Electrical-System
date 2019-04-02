void setup_reg() 
{
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  pinMode(VBATPIN, INPUT);
  pinMode(VCAPIN, INPUT);
  pinMode(IBATTPIN, INPUT);
}

void voltageRegulator() 
{
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
  
  lcd.setCursor(0, 0);
  lcd.print("vb:");
  lcd.print(vbatt);
  lcd.print(" vc:");
  lcd.print(vcap);
  lcd.setCursor(0, 1);
  lcd.print("ib:");
  lcd.print(ibatt);
}
