#define SENSOR_PIN 13

void setup()
{
    Serial.begin(9600);

    pinMode(SENSOR_PIN, INPUT);
}

void loop()
{
    if (digitalRead(SENSOR_PIN) == 1)
        Serial.println("HIGH");

    else
        Serial.println("LOW");
}