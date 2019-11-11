#include "DistanceSensorManager.h"
#include <VL53L0X.h>
#include <stdio.h>

SensorManager manager;
// VL53L0X sensor;

void tcaselect(uint8_t port, uint8_t TCAADDR) {
    // Select the sensor on different ports connected to the multiplexer
    if (port > 7) return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << port);
    Wire.endTransmission();  
}

// standard Arduino setup()
void setup() {
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Testing manager...");

    manager.setupSensors(LONG_RANGE);
    Serial.println(manager.sensorStatus, BIN);

    // tcaselect(0, 0x70);
    // sensor.init();
    // sensor.setTimeout(500);
    // sensor.setMeasurementTimingBudget(20000);
}

void loop() {
    uint16_t results[6] = {0, 0, 0, 0, 0, 0};
    manager.getDistance(results);
    for(uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        Serial.printf("%d\t", results[i]);
    }
    Serial.println();
}