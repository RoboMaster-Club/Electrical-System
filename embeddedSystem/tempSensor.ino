//TMP36 Pin Variables
int sensorPin = 0;

void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
 //Reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 
 //Converting that reading to voltage
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 //Print the voltage
 Serial.print(voltage); 
 Serial.println(" volts");
 
 // Print the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  
 Serial.print(temperatureC); Serial.println(" degrees C");//C
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");//F
 
 delay(1000);
}
