# RoboArm

## Introduction
Just when I was cleanign out some electrocnics I had, I realized that I had a pwm servo driver. I don't knwo where how it got in my electronics box, but with that my journey began on bulindg a robot arm with some servos and stepper motor. I've been wanting to create a robot arm for a long time,a dn thsi will be a ever gogin project, but we will begin with this v1 of RoboArm. I'm on my spring break right now and I should probably be studying for my midterms, but idk

## Materials 
- ESP32DevKitv1
- PWM Servo Driver
- Stepper Motor Driver. 

## Stepper Motor

### What is a Stepper motor?
A stepper motor s a type of DC mtoor that moves in little steps. It ha electromagnteic coils that creates a magentic field that moves the rotor little by little when we apply a voltage. Of crouse we control that ovltage with the GPIO pins ocnnceted to teh esp32

What sets a stepper mtoro apart from other motors is it prescision. Typical stepper motors have 200 steps to make a full rotation. you can literly control each step! Note: Stator is the stationary part of the motor. it doesnt move, but it creates the magnetic field which moves the rotor. Brushelss adn brushed motor follwo similar prociples. Stepper motros are often used in printers, 3d pritners, robotics, adn cnc machines. 


### Stepper Motor vs Brushless vs Brushed
| Feature                    | Stepper Motor                             | Brushed DC Motor                  | Brushless DC Motor (BLDC)               |
|----------------------------|-------------------------------------------|-----------------------------------|----------------------------------------|
| **Type of Rotation**        | Discrete steps (step-by-step)             | Continuous rotation               | Continuous rotation                   |
| **Control**                 | Open-loop (no feedback)                   | Open-loop (no feedback)           | Closed-loop (requires controller)     |
| **Precision**               | High precision (fixed step size)          | Moderate precision (needs encoders for precise control) | High precision (with encoder and controller) |
| **Efficiency**              | Moderate                                  | Moderate (due to friction)         | High (no brushes, less friction)      |
| **Maintenance**             | Low (no brushes to wear out)              | High (brushes wear out)            | Low (no brushes, lasts longer)         |
| **Cost**                    | Moderate to high (due to precise control) | Low                               | Higher (due to complex controller)     |
| **Common Uses**             | CNC machines, robotics, 3D printers        | Toys, fans, power tools           | Drones, electric vehicles, computers   |

### Within my code

{1, 0, 0, 0} → Only IN1 is ON

{1, 1, 0, 0} → Now IN1 & IN2 are ON

{0, 1, 0, 0} → Only IN2 is ON

{0, 1, 1, 0} → IN2 & IN3 are ON

This cycle repeats from Step 1 → Step 8 → Step 1, continuously rotating the motor.



## Servos


### What is a Servo motor?
To start, somethign I have alwasy foudn confusign is the differnece btween all the different types of servos. 

1. Postitional Servos (Standard ones)
as expeted these, when gives a speicfic postion or angle to move to they do exactly that. The hace internal feeback mechanis that tracks the psotion of the servo and continously mathces it the wanted psotion/angle. These typically workw ith PWM signals or pusle widht modulation sisginals wher ethe votlag pulse widht stermines the spotion fo the singal. for example
-1ms pulse: moves 0 degress
-1.5 pulse: moves 90 degreses
-2ms pulse: moves 180 degrees
Althoguh these are just limited to 180 degrees movemtn, they shien in their precsion. 

2. COntinuous Roation Servos
these unlike the postional servos rotate idneficndalty, like a motor. they use use sepped and direction control. they are also controleld by PWM.
- A neutral PWM pulse (usually around 1.5ms) keeps the servo stationary (no rotation).
- A pulse shorter than 1.5ms will make the servo rotate in one direction (typically clockwise).
- A pulse longer than 1.5ms will make the servo rotate in the opposite direction (counter-clockwise).
- The speed of the rotation is proportional to how far the pulse width deviates from 1.5ms.

Common Servos and thier type:
Positional
- SG90
- MG90S
- MG996R
- HS-422
- Futaba S3003
  
Coninuous 
- FS90R
- SRF30

## PCA9685 (PWM Driver IC)
The PCA9685 is a PWM controller used to control multiple servos or LEDs with precise PWM. It’s commonly used in applications where you need to control many devices simultaneously without putting too much strain on the microcontroller.
- The PCA9685 generates PWM signals using an internal clock and outputs them to the connected servos or LEDs.
- Each PWM signal can be set to a different duty cycle (i.e., how long the signal stays high versus low in each cycle).
- 16 Channels: It can control up to 16 independent PWM channels (e.g., for controlling 16 servos or LEDs), all using just 2 I2C pins from the microcontroller.
- PWM Output: It generates pulse-width modulation (PWM) signals for each of its channels, which are used to control the speed or position of devices like servos or the brightness of LEDs.

## What is PWM
PWM is a tehcnique that is used to create a varible based analog output from a digital singla. it is comonly used to control the sepedn or motors, birghtness of LEDS, and for servos. 

It works tby creatign a digital sqaure wave that swtcihes from a high and lwo threshold/ Duty cyce refers to how long the ginsla stays high vs low in each cycle. 
- 50% duty cycle: The signal is HIGH for half the time and LOW for the other half.
- 25% duty cycle: The signal is HIGH for 25% of the time and LOW for 75%.
- 100% duty cycle: The signal stays HIGH for the entire cycle (no LOW period).
  
Example of PWM for Controlling LEDs:
- A 100% duty cycle will make the LED fully on.
- A 50% duty cycle will make the LED appear dimmed, because it’s on half the time.
- A 0% duty cycle will make the LED off (always LOW).

Example of PWM for Controlling Motors:
- A 100% duty cycle will run the motor at full speed.
- A 50% duty cycle will run the motor at half speed.
- A 0% duty cycle will stop the motor.

## ESP32 Webserver and wifi
When we connectec our ESP32 to our wifi, the router gives ti a local (pricate t your pwifi) IP adress/ This adress is only aceesable from within your wifi connection. A little backgroudn on routres. Our rouyou searhc soemthign up you use that public ip adress. ter acts liek the middleman between all the devices in our home/ wifi connection adn the internet. It assigns priavet ip adresses to our devices, liek the esp32, within our wifi connection. However, the router have a internet facing public Ip that reprsetns all the devices. 

Workflow: 
lets say my laptop goes to google.com, I am actually sending a request to the praivete ip adress of my router. my router then repalces my latoptops private ip adress with its public ip adress. google.com receives the get request and sees the public ip adress from the router. This is called NAT. Netwrok Adress Trnaltion. 

Why can I only acess the webpage or ip adress o the ESP32 within my wifi connection? 
Liek I said before all our deiveces within our home have priavte ip adresses, that can only be accessed by poeple within your local wifi networl. Your router blocks, theoguh a firewall, all the exrpeinal devices from accessing the internal devices and their priavte ip adressses. 

If I Did want to be abel to acess my ESP32 anywherer, I could use port forwarding, and tel lmy router to diabsle all the security measurers for that specicif esp32 private ip adress and let nayone cess it. of coures that poses secuirty threats. 

What is a more scalable approach. NOt use a ESP32 at all and use a raspeberry pi! But in this case if I didnt want to scale this project a bit more I could have a web app hosted on a rspberry pi. Then our esp32 ocnncted to the web app, and subrcirebes to us throguh MQTT and listens in for data.



Note: OT open teh platoformio terminal do ctrl+shift+p and open PlatformIO Core CLI

Resrouces:  
(https://mischianti.org/doit-esp32-dev-kit-v1-high-resolution-pinout-and-specs/)
https://randomnerdtutorials.com/esp32-stepper-motor-28byj-48-uln2003/
https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf
https://www.instructables.com/A-Robotic-Arm-Based-on-Mg90s-Servos-and-28BYJ-48-S/ (cad files were fire)


