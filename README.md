# Robomaster Electrical System Repo
Welcome to Purdue Robomaster Club's Electrical System Repository Created by Chengming Zhang. This repository contain everything from PCB design, Design Notebook (In sub-folder's ReadMe.md), and softwares. 

If you are not familier with Robomaster, or Purdue's Robomaster Team, please refer to [Our Website](https://www.PurdueRM.com "Purdue Robomaster"). The image bellow is our latest **Electrical System Diagram** which lays out all the connection between our subsystems.

<img src = "https://github.com/RoboMaster-Club/Power-System/raw/master/Electrical Diagram.png"> 

<br>

## Team Structure

**Electrical Team Lead**: Chengming Zhang ` @cmz97` 

**Active Member:**

Henry Silva ` @Lazloian` 

Dansen Wang ` @cmz97` 

MingCheng Li ` @blaticslm` 

Ben Mirvish ` @bmivish` 



## Project Structure

📣**For detail design notebook, pls visit the coresponding directory**📣



**Project Status Symbol**

▶️ Work in-Progress

🔜 Future Project

🉑 Completed Project

🔂 New Iteration

‼️ Need Documentation

⚠️ Ship Blocker

🚮 Abanded Project

<br>

### Power Electronics

#### Super Capacitor Bank ‼️ ▶️ ⚠️

 `Made by @bmirvish @blaticslm`

Due to the competition rule, the robot chassis, which consists of four DJI 3508 geared brushless motor, can not draw more than 240W of power at any given time. To overcome this limitation, we designed our custom made supercapacitor bank as a buffer that provides instantaneous power to our robot on demand. **This Capacitor Bank only consist of voltage banlancing circuit, ADC, and the Super Capacitor Unit.** Since this is a passive electrical unit, there is no firmware.

> Plan for your PCB, Electrical Parameter and Mechinical Parameters like dimentions in your own folder‼️

> * PCB Design  @#todo‼️
> * CAD Design Enclosure @#google drive link‼️



<br>

#### Super Capacitor Charger (STM32) ‼️ 🔜 ⚠️ 🔂

`Made by @cmz97`

Since Capacitor is a short circuit when not charged, we need to design a consitance current charger to avoid damage of the battery and capacitor. Chengming Selected to use a H bridge Configuration to create a custon buck convertor using STM32F334. Currently, the Super Capacitor Charger can takes any voltage between 5v - 50v and convert it to 1v - 40v. The maxium output current is 10A. The PCB has a dimension of 2.599 in x 2.487 in and four layer. 

<br>

PCB Design @[SuperCapacitor-v2.0](https://github.com/RoboMaster-Club/Electrical-System/tree/master/SuperCapacitor-v2.0)

Firmware @[SuperCapacitor-v2.0](https://github.com/RoboMaster-Club/Electrical-System/tree/master/SuperCapacitor-v2.0)

<br>

#### Power Distribution Board 🉑

`Made by @cmz97`

Power Distribution Board is used to distribute electrical current in different voltage across the robot. Currently the Robot takes the following voltage level. 

> **24 Volt** for Robot controller, Any motor
>
> **12 Volt** for Jetson TX 2, Transparent OLED
>
> **5 Volt** for Gimbal Electrical Controller Board (ATMEGA), Electrical System Controller(ESP32)
>
> **3.3 Volt** for all the embedded chip, STM32F4, ESP32, ATMEGA
>
> **1.5 Volt** for Ammo remaining detection circuit

For a more accurate and compelete report on voltage and current usage of our robot, pls refer to [Power Distribution Board Design Log](https://github.com/RoboMaster-Club/Electrical-System/blob/master/Power-Distribution-Board-V3.0/README.md)

The newst power distribution board is divided into three seperated board:

<br>

#####Chassis Power Distribution Board

<img src = "https://raw.githubusercontent.com/RoboMaster-Club/Electrical-System/master/Power-Distribution-Board-V3.0/Chassis Power Distribution Board/Chassis-Power-Distribution-Board-sch.png">



<img src = "https://raw.githubusercontent.com/RoboMaster-Club/Electrical-System/master/Power-Distribution-Board-V3.0/Chassis Power Distribution Board/Chassis-Power-Distribution-Board.png">

This board provides all the power delivery on the robot chassis, which consist of four DJI M3508 Motor

[Chassis Power Distribution Board](https://github.com/RoboMaster-Club/Electrical-System/tree/master/Power-Distribution-Board-V3.0/Chassis%20Power%20Distribution%20Board)‼️

<br>

#####Slip-Ring Power Distribution Board

This board provides power to the Pitch Motor for the gimbal system, as well as power for Electrical System Controller. The board also provide pre-organization of the wires that goes up through the slip-ring.

[SlipRing Distribution Board](https://github.com/RoboMaster-Club/Electrical-System/tree/master/Power-Distribution-Board-V3.0/SlipRing%20Distribution%20Board)‼️

<br>

#####Gimbal Power Distribution Board

This board provides power to the STM32 Robot controller, JetsonTX2, Yall Motor, Flywheel, ammo motor, as well as the Gimbal Electrical System Controller.

[Robomater Gimbal Power Distribution Board](https://github.com/RoboMaster-Club/Electrical-System/tree/master/Power-Distribution-Board-V3.0/Robomater%20Gimbal%20Power%20Distribution%20Board)‼️



<br>
<br>


### Embedded System

#### Electrical System Controller (STM32) ‼️🔂

* PCB Design `Made by @cmz97`

* Firmware `Made by @William-An`

<br>

  

#### Remote Electrical System Monitor ‼️🔜

`Made by @cmz97`

<br>

#### Gimbal Electrical System Controller (ATMEGA) 🔂 ▶️‼️

 `Made by @Lazloian`

  System Controller uses a transparent OLED in front of the driver's camera to display information to the driver. Board recieves info from ammo detector and tof sensors

  HUD Info

  * Lines on the sides indicate walls that are close to the robot

  * Cross hairs in the center of the screen indicate low ammo in the hopper

<br>


#### Low Ammo Detection ‼️🔜

 `Made by @Lazloian`

<br>

#### Robot Controller (STM32) ‼️

<br>

#### Computer Vision System (Jetson TX 2)‼️

<br>
