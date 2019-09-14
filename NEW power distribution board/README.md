# **NEW power distribution board**
> Based on the new rules, there will be a power distribution modulus and outputing 2x10A, 1x6A, and 1x8A(reserved)

## **Stage - Data acquisition and pre-design**
> This is for optaining the useful data to do the primary design

>09/14/2019
- the data was measured from current meter
- 4 x Wheel motor
- 1 x Firing motor (Fly wheel motor)
- 1 x Gimball pitch motor (up-and-down)
- 1 x Gimball yaw motor (Left-and-right)

![QQ截图20190915025746](https://user-images.githubusercontent.com/47236078/64912627-a8311080-d764-11e9-9d4f-f0d8a4ced149.jpg)

>Problems found
- Nvidia TX2 needs at least 8A current
- 4 x Wheel motor: Must < 4.5A
- 2 x fly wheel motor: overpowered, but now fixed

>To do next
- Get the first PCB design out: for 10A? (FOR NEXT WEEK)
- Measure the firing motor current
- Draw the diagram of the Power distribution board
