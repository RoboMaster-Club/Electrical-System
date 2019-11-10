# Sensor-Integration

This is the repository for sensor integration on the standard robot and engineer robot

## Overview

The goals of this project are:
1. Use 4 ToF sensors to detect if any walls are close to the robot
2. Display if any walls are close to the HUD
3. Use limit switches on the engineer robot to detect if an object has been grabbed
4. Make a new mount for the HUD
5. Modify or select a new HUD to make it smaller / better

## Contributors

* Henry Silva (PCB Design & Code)
* Dansen Wang (CAD & Mounting)

## Updates

### Update 8 (11/9)

#### Ammo Sensor

Ammo sensor uses laser diode and photo detector to determine if ammo in the hopper is low. PCB is a ring that is placed in the hopper with diode mounted on seperate board.

### Update 7 (11/1)

#### HUD

Added low ammo indicator. Represented by four dots in the center of the screen. Wall indicator updates made faster by reducing the number of sensor readings to take the average of and by alternating pixels on the display.

#### Control Board

Finished soldering prototype, testing and final changes will be made this week.

### Update 6 (10/26)

#### ToF Code

New method for clearing the screen fixed problem of long pause in program. Wall indicators made thinner to make room for other indicators.

Under current refresh rate, hud updates can be made faster depending on the number of times to read the tof sensor. Tests concluded that 3 tof readings before taking the average is fastest while not having false positives.

The left and right tof sensors on the front and back of the robot now have different indicators for walls to give driver a better understanding of where the walls are.

Indicators added at startup to show when the hud is ready.

Demo

![Demo](./src/images/Update6/demo.gif)

### Update 5 (10/19)

#### HUD Mount

A camera holder and a bracket for the OLED screen was CADDed.
Camera Mount
![Mount](./src/images/Update5/cameraHolder.png)

Bracket for OLED was first 3D printed out with multiple slots signifying different distance the OLED screen is from the camera.

Test
![Test](./src/images/Update5/distanceTest.png)

With further testing, the ideal distance between the camera lens and the OLED screen is 0.35 inches. Modifications were made, and the OLED bracket was modified

Mount
![Mount](./src/images/Update5/oledMount.png)

Demo of the camera and OLED

Demo
![Demo](./src/images/Update5/cameraView.png)

A case to hold the photogate sensors was CADDed out as well. It's a simple plastic case with very low tolerance around the dimensions of the sensors. The case will then be glued onto the body of the robot.

Sensor Casing
![Casing](./src/images/Update5/tofMount.png)

#### OLED Control Board

Final update to the pcb. Changed button to a smaller one. XT30 for power was added. Boost was improved by adding polygons and vias. Switched from micro-USB to USB-C.

Schematic
![Schematic](./src/images/Update5/schematic.PNG)

Board

![Board](./src/images/Update5/boardV1.PNG)

### Update 4 (10/12)

#### Wall Detection

Tested final code on breadboard. Code mostly worked, but is running slowly. I think it is because of the OLED screen and the time it takes
to clear the screen. Solution is to only update the screen when necessary (keep track of what the OLED is already displaying and only update when needed)

#### OLED Control Board

Finished schematic for control board. Added USB to serial converter with the ch340 chip, reset button for the atmega, 3 pin JST connector for the ammo sensor, and micro usb connector for programming the atmega.
Decided on placement of components on board.

Schematic
![Schematic](./src/images/Update4/schematic.PNG)

Board
![Board](./src/images/Update4/board.PNG)

### Update 3 (10/7)

#### HUD Mount

A exact replica of the plate gap in front of the camera, with a holder in the middle to hold the camera, simulating camera placement.

![](./src/images/Update3/plate.png)

Mark 1 of the OLED holder, without mirror focal length calculation and OLED size on overall camera FOV consideration

![](./src/images/Update3/holderV1.png)

Mirror Drawing

![Mirror Drawing](./src/images/Update3/MirrorDrawing.png)

#### Wall Detection

Finished first version of code to show close walls on the HUD. Uses timed interrput to get sensor measurements every 4 milliseconds and update the OLED every 20 milliseconds. Average of sensor values in between OLED refreshes is used to determine close walls.
Currently untested, but will test before the next update. Planning to have the direction of the close wall be relative to the current
angle of the gimbal.

#### OLED Control Board

I chose the ATMEGA328p-au as the microcontrller. The board will have one connector for the OLED and 2 4-pin JST connectors for communication 
between the DJI control board and programming the microcontroller. No mounting holes have been added.

Schematic
![Schematic](./src/images/Update3/schematic.PNG)

Board
![Board](./src/images/Update3/board.PNG)

### Update 2 (9/28)

Made first schematic for smaller OLED breakout board. Removed all SPI related components and pins. Removed options.

SchematicV1
![SchematicV1](./src/images/Update2/SchematicV1.PNG)

Two concept drawings for the HUD element giving the driver the information about close walls. Concept 1 takes up less space and is easier for the driver to see at glance. Concept 2 is more specific, but it is up to the drivers.

Concept 1
![Concept 1](./src/images/Update2/HudConcept1.png)

Concept 2
![Concept 2](./src/images/Update2/HudConcept2.png)

### Update 1 (9/21)

#### HUD Mount

Mating Example
![Mating Example](./src/images/Update1/mating.png)

Part
![Part](./src/images/Update1/part.png)

Concept
![Concept](./src/images/Update1/concept.png)

#### ToF Integration

Got sensors to output values of 2 ToF sensors(should work for 4). Determined a measurement of 300mm to be a wall that is "close". 

Serial Output

![Serial Output](./src/images/Update1/output.PNG)

Model of Wall Detection
![Model of Wall Detection](./src/images/Update1/model.png)

Sample Output

![Sample Output](./src/images/Update1/output2.PNG)

Researched interrupt for VL53L0X sensor. Tried what might of been the interrupt pin on the current breakout board and it did not work.

Pinout
![Pinout](./src/images/Update1/pinout.PNG)
![Pinout](./src/images/Update1/pindesc.PNG)