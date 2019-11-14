void setup()
{
	Serial.begin(9600);
    pinMode(8, INPUT);
}

void loop()
{
    if (digitalRead(8))
        Serial.println("HIGH");
    else
        Serial.println("LOW");
}
