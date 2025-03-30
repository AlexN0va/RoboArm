# Roleanord (Robotic Arm)

## Introduction
While cleaning out some electronics, I discovered a PWM servo driver. I have no idea how it ended up in my electronics box, but that moment sparked my journey to build a robotic arm using servos and a stepper motor. I've wanted to create a robotic arm for a long time, and this will be an ongoing project. This is the first version (V1) of RoboArm. I should probably be studying for my midterms right now, but I couldn’t resist working on this!

## Materials
- ESP32 DevKit V1
- PWM Servo Driver
- Stepper Motor Driver

## Stepper Motor

### What is a Stepper Motor?
A stepper motor is a type of DC motor that moves in discrete steps. It has electromagnetic coils that generate a magnetic field to move the rotor incrementally when voltage is applied. We control that voltage using the GPIO pins connected to the ESP32.

What sets a stepper motor apart from other motors is its precision. Typical stepper motors have 200 steps per full rotation, allowing precise control over each movement. The stator (stationary part) creates the magnetic field that moves the rotor. Stepper motors operate on principles similar to brushless and brushed motors. They are commonly used in printers, 3D printers, robotics, and CNC machines.

### Stepper Motor vs. Brushless vs. Brushed
| Feature                    | Stepper Motor                             | Brushed DC Motor                  | Brushless DC Motor (BLDC)               |
|----------------------------|-------------------------------------------|-----------------------------------|----------------------------------------|
| **Type of Rotation**        | Discrete steps (step-by-step)             | Continuous rotation               | Continuous rotation                   |
| **Control**                 | Open-loop (no feedback)                   | Open-loop (no feedback)           | Closed-loop (requires controller)     |
| **Precision**               | High precision (fixed step size)          | Moderate (needs encoders for precision) | High (with encoder and controller) |
| **Efficiency**              | Moderate                                  | Moderate (due to friction)         | High (no brushes, less friction)      |
| **Maintenance**             | Low (no brushes to wear out)              | High (brushes wear out)            | Low (no brushes, lasts longer)         |
| **Cost**                    | Moderate to high (due to precise control) | Low                               | Higher (due to complex controller)     |
| **Common Uses**             | CNC machines, robotics, 3D printers        | Toys, fans, power tools           | Drones, electric vehicles, computers   |

### Stepper Motor Control Logic
Stepper motors operate using a sequence of signals applied to their control pins. Below is a simple step sequence for a four-phase stepper motor:

1. {1, 0, 0, 0} → Only IN1 is ON
2. {1, 1, 0, 0} → IN1 & IN2 are ON
3. {0, 1, 0, 0} → Only IN2 is ON
4. {0, 1, 1, 0} → IN2 & IN3 are ON

This cycle repeats from Step 1 → Step 8 → Step 1, continuously rotating the motor.

## Servos

### What is a Servo Motor?
There are different types of servos, each serving a specific function:

1. **Positional Servos (Standard Servos)**
   - These servos move to a specific position or angle when given a command. They have an internal feedback mechanism that ensures the servo continuously matches the desired position.
   - Typically controlled via PWM signals:
     - 1ms pulse: Moves to 0 degrees
     - 1.5ms pulse: Moves to 90 degrees
     - 2ms pulse: Moves to 180 degrees
   - Although they are limited to a 180-degree range, they are highly precise.

2. **Continuous Rotation Servos**
   - Unlike positional servos, these servos rotate indefinitely, like a motor. They are controlled by PWM to adjust speed and direction:
     - A neutral PWM pulse (~1.5ms) keeps the servo stationary.
     - A pulse < 1.5ms rotates the servo in one direction.
     - A pulse > 1.5ms rotates the servo in the opposite direction.
   - The speed depends on how much the pulse width deviates from 1.5ms.

**Common Servos and Their Types:**
- **Positional:** SG90, MG90S, MG996R, HS-422, Futaba S3003
- **Continuous Rotation:** FS90R, SRF30

## PCA9685 (PWM Driver IC)
The PCA9685 is a PWM controller used to control multiple servos or LEDs with precise PWM, reducing the strain on the microcontroller.
- **16 Channels:** Controls up to 16 servos or LEDs using just 2 I2C pins.
- **PWM Output:** Generates independent PWM signals for each channel.
- **Duty Cycle Control:** Varies the pulse width to adjust servo position or LED brightness.

## What is PWM?
PWM (Pulse Width Modulation) is a technique used to generate an analog output from a digital signal, commonly used for controlling motor speed, LED brightness, and servos.
- 50% duty cycle: Signal is HIGH for half the time.
- 25% duty cycle: Signal is HIGH for 25% of the time.
- 100% duty cycle: Signal stays HIGH continuously.

### PWM in Practice
- **LEDs:**
  - 100% duty cycle = Fully ON
  - 50% duty cycle = Dimmed
  - 0% duty cycle = OFF
- **Motors:**
  - 100% duty cycle = Full speed
  - 50% duty cycle = Half speed
  - 0% duty cycle = Stopped

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

