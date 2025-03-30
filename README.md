# Roleanord (Robotic Arm)

## Introduction
Just when I was cleaning out some electronics I had, I realized that I had a PWM servo driver. I don't know how it got in my electronics box, but with that, my journey began on building a robot arm with some servos and a stepper motor. I've been wanting to create a robot arm for a long time, and this will be an ever-going project, but we will begin with this v1 of RoboArm. I'm on my spring break right now, and I should probably be studying for my midterms, but idk.

## Materials 
- ESP32DevKitv1
- PWM Servo Driver
- Stepper Motor Driver

## Stepper Motor

### What is a Stepper Motor?
A stepper motor is a type of DC motor that moves in little steps. It has electromagnetic coils that create a magnetic field that moves the rotor little by little when we apply a voltage. Of course, we control that voltage with the GPIO pins connected to the ESP32.

What sets a stepper motor apart from other motors is its precision. Typical stepper motors have 200 steps to make a full rotation. You can literally control each step! Note: The stator is the stationary part of the motor. It doesn’t move, but it creates the magnetic field that moves the rotor. Brushless and brushed motors follow similar principles. Stepper motors are often used in printers, 3D printers, robotics, and CNC machines.

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

### Within My Code

{1, 0, 0, 0} → Only IN1 is ON

{1, 1, 0, 0} → Now IN1 & IN2 are ON

{0, 1, 0, 0} → Only IN2 is ON

{0, 1, 1, 0} → IN2 & IN3 are ON

This cycle repeats from Step 1 → Step 8 → Step 1, continuously rotating the motor.

## Servos

### What is a Servo Motor?
To start, something I have always found confusing is the difference between all the different types of servos. 

1. **Positional Servos (Standard ones)**
As expected, these, when given a specific position or angle to move to, do exactly that. They have an internal feedback mechanism that tracks the position of the servo and continuously matches it to the wanted position/angle. These typically work with PWM signals or pulse-width modulation signals, where the voltage pulse width determines the position of the signal. For example:
- 1ms pulse: moves 0 degrees
- 1.5ms pulse: moves 90 degrees
- 2ms pulse: moves 180 degrees
Although these are just limited to 180 degrees movement, they shine in their precision. 

2. **Continuous Rotation Servos**
These, unlike the positional servos, rotate indefinitely like a motor. They use speed and direction control. They are also controlled by PWM.
- A neutral PWM pulse (usually around 1.5ms) keeps the servo stationary (no rotation).
- A pulse shorter than 1.5ms will make the servo rotate in one direction (typically clockwise).
- A pulse longer than 1.5ms will make the servo rotate in the opposite direction (counter-clockwise).
- The speed of the rotation is proportional to how far the pulse width deviates from 1.5ms.

### Common Servos and Their Type:
**Positional**
- SG90
- MG90S
- MG996R
- HS-422
- Futaba S3003
  
**Continuous**
- FS90R
- SRF30

## PCA9685 (PWM Driver IC)
The PCA9685 is a PWM controller used to control multiple servos or LEDs with precise PWM. It’s commonly used in applications where you need to control many devices simultaneously without putting too much strain on the microcontroller.
- The PCA9685 generates PWM signals using an internal clock and outputs them to the connected servos or LEDs.
- Each PWM signal can be set to a different duty cycle (i.e., how long the signal stays high versus low in each cycle).
- **16 Channels**: It can control up to 16 independent PWM channels (e.g., for controlling 16 servos or LEDs), all using just 2 I2C pins from the microcontroller.
- **PWM Output**: It generates pulse-width modulation (PWM) signals for each of its channels, which are used to control the speed or position of devices like servos or the brightness of LEDs.

## What is PWM?
PWM is a technique that is used to create a variable-based analog output from a digital signal. It is commonly used to control the speed of motors, brightness of LEDs, and for servos. 

It works by creating a digital square wave that switches from a high and low threshold. Duty cycle refers to how long the signal stays high vs low in each cycle. 
- 50% duty cycle: The signal is HIGH for half the time and LOW for the other half.
- 25% duty cycle: The signal is HIGH for 25% of the time and LOW for 75%.
- 100% duty cycle: The signal stays HIGH for the entire cycle (no LOW period).
  
Example of PWM for Controlling LEDs:
- A 100% duty cycle will make the LED fully on.
- A 50% duty cycle will make the LED appear dimmed because it’s on half the time.
- A 0% duty cycle will make the LED off (always LOW).

Example of PWM for Controlling Motors:
- A 100% duty cycle will run the motor at full speed.
- A 50% duty cycle will run the motor at half speed.
- A 0% duty cycle will stop the motor.

## ESP32 Webserver and Wi-Fi
When we connect our ESP32 to Wi-Fi, the router assigns it a local (private) IP address. This address is accessible only within the local network.

### How Routing Works
When you visit a website, your request goes to your router, which replaces your device’s private IP with the router’s public IP. This is called **Network Address Translation (NAT)**.

### Why Can't We Access the ESP32 from Outside the Network?
Devices within the home network have private IP addresses that are not accessible from the internet due to firewall protections. To access the ESP32 externally, we could:
1. **Use Port Forwarding** (Not recommended due to security risks).
2. **Host a Web App on a Raspberry Pi** and have the ESP32 connect to it via MQTT for scalable control.

## Web App

### WebServer Library (Synchronous)
- Handles requests one at a time.
- Each request must be processed before handling the next one.
- Simple to implement but can be slow.

### ESPAsyncWebServer Library (Asynchronous)
- Uses an event-driven approach.
- Handles multiple client connections simultaneously.
- Uses **AsyncTCP** to avoid blocking operations.
- Allows the ESP32 to perform multiple tasks while handling network requests.

### TCP Overview
TCP (Transmission Control Protocol) ensures reliable and ordered data transmission.
- Establishes a connection before sending data.
- Uses acknowledgments (ACKs) to confirm data delivery.
- Asynchronous TCP doesn’t wait for acknowledgments; instead, it uses **callbacks** to handle events efficiently.

This project is a work in progress, and I’m excited to continue developing it. Stay tuned for updates!

