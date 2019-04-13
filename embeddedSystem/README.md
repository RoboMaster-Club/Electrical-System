# Embedded System

This folder contains Arduino code (or future code) for the Super Capacitor Booster Project.

## Usage

To implement the code, simply import it to the Arduino IDE with corresponding library installed.

## Contributing

Charlotte Huang, Roshni Sarma, Megan Singer, William An

## Progress

VoltageRegulator.ino reads voltage of the battery, voltage of capacitor, current of battery to decide whether it boosts, and display the result on the LCD screen.
(Once the other .inos are finished, they will be put on this colunm)

## Notes

1. Make all libraries static
   1. Used libraries
      1. https://github.com/me-no-dev/AsyncTCP
      2. https://github.com/me-no-dev/ESPAsyncWebServer
1. Add RTC reading

## Electrical System Monitor

* Todos
  * Sensors
    * Data Logging
    * Sensors reading
  * Serial
    * Create debug port?
  * Threading issue?
  * Web
    * Speed increasing?
    * Turn off animation
    * Log
      * Log file management
      * Log file download
      * Log file plotting
        * [ESP32 SD Flush not working](https://github.com/espressif/arduino-esp32/issues/1293), use newest release version
    * Reconnection button
    * Status
    * setting
      * Set mode of system
      * Set ssid, pass, hostname (eeprom)
    * Embed css and js files to avoid running out of mem?
  * Extendability
    * Able to use in the next season
* API Explanation
  * `/`
    * Handle logging chart display
  * `/log`
    * Provide logging file downloads 
  * `/status`
    * Whether each module is online or not
  * `/setting`
    * Mode selection
      * Super cap MODE
      * mix mode
      * battery only mode
* WebSocket Event
  * connect
    * server broadcast current sensor data to this client
  * disconnect
    * cleanup
  * data
    * sensor data
