#include "src/PowerDistributionBoard.h"

    // Note you can only read analog inputs on ADC #1 once WiFi has started
    // Include A2 A3 A4 13 33 32 
    // https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
# define VBATPIN A4
# define VCAPIN  13
# define IBATTPIN  A2
# define VRATIO 30.0
# define VMIN 1

PDP pdp(VBATPIN, VCAPIN, IBATTPIN);
float vBatt = 0; //votage of battery
float vCap = 0; //votage of capacitor
float iBat = 0; //current of battery
float temp = 0;
bool boost = false; //whether it boosts

void setup() {
    Serial.begin(115200);
    Serial.println("Voltage Regulator test");
}

void loop() {
    //reading data from mainboard
    vBatt = pdp.getBatteryVoltage(); //A6
    vCap = pdp.getCapacitorVoltage(); //A9
    iBat = pdp.getBatteryCurrent(); //A10
    Serial.printf("VBatt: %.2f\tVCap: %.2f\tIBat: %.2f\n", vBatt, vCap, iBat);
    delay(1000);
}
  