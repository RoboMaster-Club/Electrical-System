# Robomaster-Controller-Board-v4.0:+1:
This board controls the movement of engineering robot's arm and makes it able to grab box of ammos. This board **REQUIRES** 24V Input.

## Components

**Relays**

 There are four relays on the board, three of them controls the robot arm's three different motion: vertical, horizontal, and rotational. The rest one is a back up relay.

**Sensors**
  1. Ammo-Detection Sensor 
  2. Limit Switch
  3. Vision
  4. TOF

**Bluetooth**

Bluetooth enables us to control the engineer robot with our phone.

**Buck Converter**

The buck converter receives 24V input and outputs 3.3V for the microcontroller.

**LED**

LED is for debugging.

## Connectors
| Connector Name  | Connected Object | 
| ------------- | ------------- |
| I2C_1 () | IMU  |
| I2C_2 () | Multi Plexer (Three TOFs)  |
| I2C_3 () | TMU_extra  |
| I2C_4 () | Multi Plexer_extra |
| RELAY1 | Vertical Pneumatic Control (24V output) |
| RELAY2 | Horizontal Pneumatic Control (24V output) |
| RELAY3 | Rotational Pneumatic Control (24V output) |
| CANBUS | Arm Motors |

## Schematic & Board Design
Pin Connections
![alt text](https://github.com/wsy0240/Calculator/blob/master/image.png)
Micro Controller
![alt text](https://github.com/wsy0240/Calculator/blob/master/Micro%20Controller.png)
Buck Converter
![alt text](https://github.com/wsy0240/Calculator/blob/master/Buck%20Converter.png)
Bluetooth Module
![alt text](https://github.com/wsy0240/Calculator/blob/master/Bluetooth%20Module.png)
Connectors
![alt text](https://github.com/wsy0240/Calculator/blob/master/Connectors.png)