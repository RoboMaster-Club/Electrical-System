#ifndef PDP_H
#define PDP_H
/**
 * TODO Update to the newest pdp design; integrate temperature and ADC IC
 **/

// Include
#include <stdint.h>
#include <Arduino.h>

// Constant goes here

// Declaration goes here
class PDP {
    public:
        float getBatteryVoltage();
        float getCapacitorVoltage();
        float getBatteryCurrent();
        bool canBoost();

        // Note you can only read analog inputs on ADC #1 once WiFi has started
        // Include A2 A3 A4 13 33 32 
        // https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
        PDP(uint8_t vBattPin, uint8_t vCapPin, uint8_t iBattPin);
    private:
        uint8_t vBattPin;
        uint8_t vCapPin;
        uint8_t iBattPin;
        float vBoostRef;
        float vCapMax;
        float vBatMax;
        static const uint16_t ANALOG_RANGE = 4095;
        static const uint16_t CURRENT_REF = 500;
        static constexpr float CURRENT_RATIO = 0.004;
        static constexpr float VOLTAGE_MAX = 30.0;
        static const uint8_t CAPACITOR_MIN = 12;  // Minimum voltage for capacitor boosting, 12 V
};

#endif