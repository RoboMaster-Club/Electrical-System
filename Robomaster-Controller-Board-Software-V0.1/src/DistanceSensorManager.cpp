#include "DistanceSensorManager.h"

#define ADDRESS_DEFAULT 0x29

SensorManager::SensorManager(uint8_t TCAADDR) {
    managerAddr = TCAADDR;
}

void SensorManager::setupSensors(uint8_t config) {
    Serial.println("Setuping up sensors");
    for(uint8_t i = 0; i < NUM_SENSORS; i++) {
        tcaselect(i, managerAddr);
        VL53L0X sensor;
        sensors[i] = sensor;
        uint8_t data;
        Serial.printf("Manager: %xd, No: %d, Addr: %xd\n", managerAddr, i, ADDRESS_DEFAULT);
        if (Wire.writeTransmission(ADDRESS_DEFAULT, &data, 0, 1) == I2C_ERROR_OK) {
            Serial.printf("No. %d online\n", i);
            sensor.init();
            sensorStatus |= 1;
            sensorStatus <<= 1;
            sensor.setTimeout(500);
            switch (config)
            {
                default:
                case HIGH_SPEED:
                    sensor.setMeasurementTimingBudget(20000);
                    break;
                case LONG_RANGE:
                    // lower the return signal rate limit (default is 0.25 MCPS)
                    sensor.setSignalRateLimit(0.1);
                    // increase laser pulse periods (defaults are 14 and 10 PCLKs)
                    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
                    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
                    break;
                case HIGH_ACCURACY:
                    sensor.setMeasurementTimingBudget(200000);
                    break;
                
            }
        } else {
            sensorStatus |= 0;
            sensorStatus <<= 1;
        }
        
    }
}

void SensorManager::getDistance(uint16_t* dst) {
    for(uint8_t i = 0; i < NUM_SENSORS; i++) {
        uint8_t selector = 1 << (NUM_SENSORS - i);
        // Sensor not online
        if (!(selector & sensorStatus)) {
            *(dst + i) = 0;
            continue;
        }
        tcaselect(i, managerAddr);
        VL53L0X sensor = sensors[i];
        *(dst + i) = sensor.readRangeSingleMillimeters();
    }
    // Serial.printf("Function: %p, %d\n", dst, *dst);
    return;
}