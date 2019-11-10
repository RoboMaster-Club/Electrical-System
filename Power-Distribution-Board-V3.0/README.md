# **NEW power distribution board**
> Based on the new rules, there will be a power distribution modulus and outputing 2x10A, 1x6A, and 1x8A(reserved)

## **Stage - Data acquisition and pre-design**
> This is for optaining the useful data to do the primary design

### 09/14/2019
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

### 09/27/2019
> The specific current capacities for two 10A rail and 6A rail are below
- 10A rail 1
> ![10A-A](https://user-images.githubusercontent.com/47236078/65800601-74fd7100-e1a9-11e9-9c39-6496de4b726e.png)

- 10A rail 2
> ![10A-B](https://user-images.githubusercontent.com/47236078/65800627-8777aa80-e1a9-11e9-82e2-c08141d560e1.png)

- 6A rail
> ![6A](https://user-images.githubusercontent.com/47236078/65800599-74fd7100-e1a9-11e9-868b-fbf22b490e38.png)

- To do next
> Keep doing the PCB for 10A rail A and B schemetic (By Saturday)

> Measure TX2 current
