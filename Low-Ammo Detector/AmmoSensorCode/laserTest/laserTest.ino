#define SENSOR_PIN 8

void setup()
{
    Serial.begin(9600);

    pinMode(SENSOR_PIN, INPUT);
}

void loop()
{
    if (digitalRead(SENSOR_PIN))
        Serial.println("HIGH");
    else
        Serial.println("LOW");
    delay(100);
}
