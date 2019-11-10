/*
Author: Henry Silva
Notes:
    - The ToF sensors on the I2C multiplexer will initialized
    starting on port 0 and continue to the number of ToF sensors - 1
    so pay attention to the ports that the sensors are connected to

    - Code assumes that the front two ToF sensors are 0 and 1, the back sensors are 2 and 3, the left
    ToF sensor is 4, and the right  sensor is 5

    - Code will currently light up the wall that is close relative to the front of the robot, not to the driver's view
    TODO: HUD update is now dependant on the tof cycle time, find a way to get sensor readings faster
*/
#include <Wire.h>
#include <VL53L0X.h>
#include "HyperDisplay_UG2856KLBAG01.h"

#define TCAADDR 0x70 // address of the I2C multiplexer
#define NUM_SENSORS 2 // number of ToF sensors
#define OLED_PORT 2 // the port that the OLED is connected to on the I2C multiplexer
#define WALL_CLOSE 300 // a number in mm that will mean a wall is close
#define HUD_CYCLE 20 // HUD refresh rate in milliseconds
#define TOF_CYCLE 4 // time between ToF readings in milliseconds
#define NUM_READINGS 3 // number of ToF readings to take the average of
#define CLOSE_DISTANCE 300 // distance of a wall that is "close" in millimeters
#define RETICLE 6 // spacing of the ammo indicator crosshair

VL53L0X tofSensors[NUM_SENSORS]; // VL53L0X ToF sensor array
UG2856KLBAG01_I2C hud; // sparkfun transparent oled HUD

volatile boolean checkToF = false; // will be true when that ToF sensors will be checked
volatile boolean updateHud = false; // will be true when the HUD is updated
unsigned long currentTime; // current time in milliseconds
unsigned long previousTime; // time that has passed since last HUD cycle
int tofReadings[NUM_SENSORS * 5]; // 5 most recent ToF readings
int tofReadingNum = 0; // current number of ToF readings taken since last HUD refresh
double tofAverage[NUM_SENSORS]; // array of all most recent 5 ToF sensors readings
int currentState[NUM_SENSORS]; // the current state of a wall being close
int lastState[NUM_SENSORS]; // the last state of the tof sensor

void setup()
{
    // start serial and wire
    Serial.begin(9600);
    Serial.println("Starting Up");
    Wire.begin();
    Wire.setClock(400000);

    // initialize HUD
    Serial.println("Initializing HUD");
    tcaPortSelect(OLED_PORT);
    hud.begin(); // this will initialize oled with defaults
    for (int i = 0; i < 7; i++)
        hudUpdate(i, 1);
    Serial.println("HUD ready");

    // initialize all sensors
    Serial.println("Initializing ToF sensors");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print("Sensor ");
        Serial.print(i);
        tcaPortSelect(i);
        VL53L0X tofSensor; // sensors on the current multiplexer port
        tofSensors[i] = tofSensor;
        tofSensors[i].init();
        tofSensors[i].setTimeout(500);
        tofSensors[i].setMeasurementTimingBudget(20000); // configuration for long range
        Serial.print(" Ready\n");
    }
    Serial.println("ToF sensors ready\n");
    tcaPortSelect(OLED_PORT);
    for (int i = 0; i < 7; i++)
        hudUpdate(i, 0);
}

void loop()
{
    // set timer equal to the current time
    currentTime = millis();

    //check if ToF senors should be checked
    if (currentTime - previousTime >= TOF_CYCLE)
    {
        //Serial.print("Interrupt ");
        //Serial.println(tofReadingNum + 1);
        checkToF = true;
        previousTime = currentTime;
    }

    if (checkToF)
    {
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            tofReadings[(NUM_SENSORS * tofReadingNum) + i] = readToF(i);
            //Serial.print("Tof read ");
            //Serial.print(i);
            //Serial.print(": ");
            //Serial.print(tofReadings[i * tofReadingNum]);
            //Serial.println();
        }
        //Serial.println();
        tofReadingNum += 1;
        checkToF = false;
    }

    if (tofReadingNum > NUM_READINGS - 1)
    {
        tcaPortSelect(OLED_PORT);
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            int tofTotal = 0; // total of last 5 sensor readings
            for (int j = 0; j < NUM_READINGS; j++)
            {
                tofTotal += tofReadings[i + (NUM_SENSORS * j)];
            }
            tofAverage[i] = tofTotal / NUM_READINGS;
            Serial.print("ToF Average " );
            Serial.print(i);
            Serial.print(": ");
            Serial.println(tofAverage[i]);
        }
        Serial.println();

        // update oled here
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            if (tofAverage[i] <= CLOSE_DISTANCE)
            {
                currentState[i] = 1;
            }
            else
            {
                currentState[i] = 0;
            }
            if (currentState[i] != lastState[i])
            {
                Serial.println("HUD Update");
                hudUpdate(i, currentState[i]);
            }
            lastState[i] = currentState[i];
        }
        tofReadingNum = 0;
    }
}

void tcaPortSelect(uint8_t port)
{
    if (port > 7)
        return;
    
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << port);
    Wire.endTransmission();
}

void hudUpdate(int sensor, int state)
{
    if (sensor == 0)
    {
        if (state)
            showPixels(25, 62, 2, 1, 3);
        else
            clearPixels(25, 62, 2, 1, 3);
    }
    else if (sensor == 1)
    {
        if (state)
            showPixels(63, 100, 2, 1, 3);
        else
            clearPixels(63, 100, 2, 1, 3);
    }
    else if (sensor == 2)
    {
        if (state)
            showPixels(25, 62, 60, 1, 2);
        else
            clearPixels(25, 62, 60, 1, 2);
    }
    else if (sensor == 3)
    {
        if (state)
            showPixels(63, 100, 60, 1, 2);
        else
            clearPixels(63, 100, 60, 1, 2);
    }
    else if (sensor == 4)
    {
        if (state)
            showPixels(16, 48, 2, 0, 2);
        else
            clearPixels(16, 48, 2, 0, 2);
    }
    else if (sensor == 5)
    {
        if (state)
            showPixels(16, 48, 125, 0, 2);
        else
            clearPixels(16, 48, 125, 0, 2);
    }
    else if (sensor == 6)
    {
        if (state)
        {
            hud.pixelSet(64 - RETICLE, 32);
            hud.pixelSet(64 + RETICLE, 32);
            hud.pixelSet(64, 32 - RETICLE);
            hud.pixelSet(64, 32 + RETICLE);
        }
        else
        {
            hud.pixelClear(64 - RETICLE, 32);
            hud.pixelClear(64 + RETICLE, 32);
            hud.pixelClear(64, 32 - RETICLE);
            hud.pixelClear(64, 32 + RETICLE);
        }
    }
}
// start and stop for pixels, pos for the x or y cor to draw the line, rotation 1 = horizontal, 0 = vertical
void showPixels(int start, int stop, int pos, int rotation, int spacing)
{
    for (int i = start; i <= stop; i += spacing)
    {
        if (rotation)
            hud.pixelSet(i, pos);
        else
            hud.pixelSet(pos, i);
    }
}

// start and stop for pixels, pos for the x or y cor to draw the line, rotation 1 = horizontal, 0 = vertical
void clearPixels(int start, int stop, int pos, int rotation, int spacing)
{
    for (int i = start; i <= stop; i += spacing)
    {
        if (rotation)
            hud.pixelClear(i, pos);
        else
            hud.pixelClear(pos, i);
    }
}
int readToF(uint8_t port)
{
    tcaPortSelect(port);
    return tofSensors[port].readRangeSingleMillimeters();
}