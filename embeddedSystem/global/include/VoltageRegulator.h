#ifndef VOLTAGE_REGULATOR_H
#define VOLTAGE_REGULATOR_H

// Include
#include <stdint.h>
#include <Arduino.h>

// Constant goes here

// Declaration goes here
class VoltageRegulator {
    public:
        float getBatteryVoltage(void);
        float getCapacitorVoltage(void);
        float getBatteryCurrent(void);
        bool canBoost(void);
        VoltageRegulator(uint8_t vBattPin, uint8_t vCapPin, uint8_t iBattPin, float vCapMax, float vBatMax, float vBoostRef);
    private:
        uint8_t vBattPin;
        uint8_t vCapPin;
        uint8_t iBattPin;
        float vBoostRef;
        float vCapMax;
        float vBatMax;
};

#endif