#ifndef DISTANCE_SENSOR_MANAGER_H
#define DISTANCE_SENSOR_MANAGER_H

/**
 * The manager library for distance sensor based on VL530LX
 * Using TCA9548A I2C multiplexer for reading various sensors
 * 
 * TODO Use generic class for distance sensor for different types of sensor in the future
 * TODO Extend use for more than distance sensor
 **/

#include <VL53L0X.h>
#include <Arduino.h>
#include "Wire.h"
#include <stdint.h>

// Sensor configuration
#define HIGH_SPEED 1
#define HIGH_ACCURACY 2
#define LONG_RANGE 4
#define NUM_SENSORS 6

class SensorManager 
{
    public:
        SensorManager(uint8_t TCAADDR=0x70);
        void getDistance(uint16_t*);
        void setupSensors(uint8_t config=HIGH_SPEED);
        VL53L0X sensors[NUM_SENSORS];
        uint8_t sensorStatus = 0;
    private:
        static void tcaselect(uint8_t port, uint8_t TCAADDR) {
            // Select the sensor on different ports connected to the multiplexer
            if (port > 7) return;
            Wire.beginTransmission(TCAADDR);
            Wire.write(1 << port);
            Wire.endTransmission();  
        }
        uint8_t managerAddr;
};


#endif