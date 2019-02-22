# **Supercapacitor power distribution test**
> For validating the design, it is necessary to simulate or create the actual circuit to see whether the design matches the expection. 

## **code has been in the folder**

## **Stage 1**
> Feb,2,2019

Validating the charging, discharging, and detection functionality by using Analog output

>**Charging Circuit**
- discription: A1 is to control the charging current flow and set the voltage P1 to turn on MOSFET P1
- P1 links to MOSFET gate, and Vgate to source should be -10V

![20190208064819](https://user-images.githubusercontent.com/47236078/52451157-d1f3da80-2b78-11e9-9160-7237cf4590af.png)
![qq 20190208082002](https://user-images.githubusercontent.com/47236078/52451539-63178100-2b7a-11e9-8c67-8dc2c8dcac4a.jpg)

>**Discharging circuit**
- discription: A2 is to control the discharging of the supercapacitor to turn on MOSFET P2
- Vgate to source of MOSFET P2 is -8V with 8bit analog output value 255

![qq 20190208072129](https://user-images.githubusercontent.com/47236078/52451378-b0472300-2b79-11e9-8d47-4b1209a018c3.jpg)
![mosfetp2](https://user-images.githubusercontent.com/47236078/52451861-a7efe780-2b7b-11e9-9084-b49909b339e1.jpg)

>**Detecting circuit**
- discription: The purpose of this circuit is to detect the supercapacitor's voltage by analog input
- Failed, it needs to be redesign. 
- After analog input reading reaches 76/1023, the value stays constant

![qq 20190208070718](https://user-images.githubusercontent.com/47236078/52451397-c654e380-2b79-11e9-9a8b-113af8291b56.jpg)

## **Stage 2**
>Feb.15, 2019

Supercapacitor voltage detecting circuit modification

>Board modification
![qq 20190222134428](https://user-images.githubusercontent.com/47236078/53222323-2d10eb80-36a8-11e9-92af-49cb25383e23.jpg)
- The diameters of the connector holes expand to 0.95mm due to wrong calculations(P4 and P2 connector)
- MOSFETs (Bottom 2 red areas) and  Schottky diode array (upper right) are placed on the exposure copper plate (red area). 
- Some wire widh has been adjusted. 
- circuit detecting circuit has been formally modified (first time). 
- P2 connection has been changed to 5V from A3-detect. 

>Detection circuit
- Read the value correctly from A3-DETECT

![qq 20190222140208](https://user-images.githubusercontent.com/47236078/53222925-79f5c180-36aa-11e9-9f79-3a7b80bee091.jpg)

>Next Plan
- Go EE to get components. 
- Test Supercapacitors: teammate responses for.
- Learn LT SPICE with Matthew. 
- Overall supercapacitor program in Arduino. 
