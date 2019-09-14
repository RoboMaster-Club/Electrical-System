const int PWMPin = 2; //pwm pin
const int analogPin = A0; //analog input


int PWMvalue; //pwm output shown
int AnalogValue; //analog input shown
int detect; //detect read

void setup() {
  Serial.begin(9600);
  pinMode(PWMPin, OUTPUT);
}

void loop() {

AnalogValue = analogRead(analogPin); //reading analog pin value

detect = analogRead(A2); //detection analog reading

PWMvalue = map(AnalogValue, 0, 1023, 0, 255); //map analog value to analog output

analogWrite(PWMPin, PWMvalue); //analog output

//monitoring the value
Serial.print("AnalogValue = ");
Serial.print(AnalogValue);
Serial.print("\t PWMvalue = ");
Serial.print(PWMvalue);
Serial.print("\t A3_read = ");
Serial.print(detect);
Serial.print("\n");

delay(1000);
}
