//Include Libraries
#include "Wire.h"
#include "WiFi.h"
#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_MCP9808.h"

//Defining Pins
# define VBATPIN A0
# define VCAPIN  A1
# define IBATTPIN  A2
# define VRATIO 30.0//votage ratio: max voltage displayed
# define VMIN 1
# define VBOOST A3
# define RX 10
# define TX 11

//Defining Constants

float vbatt = 0; //votage of battery
float vcap = 0; //votage of capacitor
float ibatt = 0; //current of battery
float tempC = 0;
float tempF = 0;
bool boost = false; //whether it boosts

Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
//SoftwareSerial esp32(RX, TX);

// Replace with your network credentials
const char* ssid     = "RM-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//Function Protoypes
void setup() {
  setup_AP();
  setup_temp();
  setup_reg();
}

void loop() {
  loop_AP();
//  loop_temp();
//  loop_reg();
}
