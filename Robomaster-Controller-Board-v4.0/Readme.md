# Robomaster-Controller-Board-v4.0:+1:
This board controls the movement of engineering robot's arm and makes it able to grab box of ammos.

## Components

**Relays**
 
 There are four relays on the board, three of them controls the robot arm's three different motion: vertical, horizontal, and rotational. The rest one is a back up relay.

**Sensors**
  1. Ammo-Detection Sensor 
  2. Limit Switch
  3. Vision
  4. TOF
  
**Bluetooth**

**Buck Converter**

**LED**
  
## Connectors
| Connector Name  | Connected Object |
| ------------- | ------------- |
| I2C_1  | TOF1  |
| I2C_2  | TOF2  |
| I2C_3  | TOF3  |
| I2C_4 | TOF1_Extra |
| I2C_5 | TOF2_Extra  |
| I2C_6  | TOF3_Extra  |
| RELAY1 | Vertical Pneumatic Control |
| RELAY2 | Horizontal Pneumatic Control  |
| RELAY3 | Rotational Pneumatic Control  |
| CANBUS | Arm Motors |
