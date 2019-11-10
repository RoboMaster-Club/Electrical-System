#include <VL53L0X.h>
#include <Wire.h>

//TODO: try using millis() for interrput with the freqeuncy of the timing sensors

#define TCAADDR 0x70 // address of the I2C Multiplexer
#define NUM_SENSORS 2 // number of ToF sensors
#define INT_PIN 2 // interrupt pin
#define WALL_CLOSE 300 // a wall is close if it is within 300 mm

VL53L0X sensors[NUM_SENSORS]; // VL53L0X sensor array

volatile boolean ready = false;
boolean usingInterrupt = false; // set true if using interrupt

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    Serial.println("Starting Up");

    //pinMode(INT_PIN, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(INT_PIN), sensorReady, CHANGE);

    // initialize and configure all sensors in the array
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        tcaselect(i);
        VL53L0X sensor;
        sensors[i] = sensor;
        sensors[i].init();
        sensors[i].setTimeout(500);
        sensors[i].setMeasurementTimingBudget(20000); // configuration for LONG_RANGE mode
    }

    Serial.println("Sensors Ready");
}

void loop()
{
    if (!usingInterrupt)
    {
        // print sensor measurements to the serial monitor
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            tcaselect(i);
            //Serial.println("Sensor " + String(i) + ": " + String(sensors[i].readRangeSingleMillimeters()));
            if (sensors[i].readRangeSingleMillimeters() <= WALL_CLOSE)
            {
                Serial.println("Wall Close: " + String(i));
            }
        }
    }
    else
    {
        // displays sensor 0 value if interrupt
        tcaselect(0);
        if (ready)
        {
            ready = !ready;
            tcaselect(0);
            Serial.println("Sensor 0 on interrupt: " + String(sensors[0].readRangeSingleMillimeters()));
        }
    }
    Serial.println();
}

// function to select the port on the I2C multiplexer
void tcaselect(uint8_t port)
{
    if (port > 7)
    {
        return;
    }

    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << port);
    Wire.endTransmission();
}

// funciton called on interrupt that changes the state of the read variable. Sensor on port 0 of multiplexer is attacted to interrupt
void sensorReady()
{
    ready = !ready;
}