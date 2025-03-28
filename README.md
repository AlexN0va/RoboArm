# RoboArm

## INtroduction

Just when I was cleanign out some electrocnics I had, I realized that I had a pwm servo driver. I don't knwo where how it got in my electronics box, but with that my journey began on bulindg a robot arm with some servos and stepper motor. I've been wanting to create a robot arm for a long time,a dn thsi will be a ever gogin project, but we will begin with this v1 of RoboArm. 

## Materials 
ESP32DevKitv1
PWM Servo Driver
Stepper Motor Driver. 


# Stepper Motor

### What is a Stepper motor?
A stepper motor s a type of DC mtoor that moves in little steps. It ha electromagnteic coils that creates a magentic field that moves the rotor little by little when we apply a voltage. Of crouse we control that ovltage with the GPIO pins ocnnceted to teh esp32

What sets a stepper mtoro apart from other motors is it prescision. Typical stepper motors have 200 steps to make a full rotation. you can literly control each step! Note: Stator is the stationary part of the motor. it doesnt move, but it creates the magnetic field which moves the rotor. Brushelss adn brushed motor follwo similar prociples. Stepper motros are often used in printers, 3d pritners, robotics, adn cnc machines. 


### **🔍 Differences in a Nutshell**
| Feature                    | Stepper Motor                             | Brushed DC Motor                  | Brushless DC Motor (BLDC)               |
|----------------------------|-------------------------------------------|-----------------------------------|----------------------------------------|
| **Type of Rotation**        | Discrete steps (step-by-step)             | Continuous rotation               | Continuous rotation                   |
| **Control**                 | Open-loop (no feedback)                   | Open-loop (no feedback)           | Closed-loop (requires controller)     |
| **Precision**               | High precision (fixed step size)          | Moderate precision (needs encoders for precise control) | High precision (with encoder and controller) |
| **Efficiency**              | Moderate                                  | Moderate (due to friction)         | High (no brushes, less friction)      |
| **Maintenance**             | Low (no brushes to wear out)              | High (brushes wear out)            | Low (no brushes, lasts longer)         |
| **Cost**                    | Moderate to high (due to precise control) | Low                               | Higher (due to complex controller)     |
| **Common Uses**             | CNC machines, robotics, 3D printers        | Toys, fans, power tools           | Drones, electric vehicles, computers   |

---

### **Why Choose One Over the Other?**
- **Stepper Motors** are great when you need precise **position control** in an **open-loop system** (no feedback needed).
- **Brushed DC Motors** are cheap and simple, making them ideal for simple applications like toys or small appliances.
- **Brushless DC Motors (BLDC)** are the go-to for high-efficiency, **high-performance** applications like **electric vehicles** or **drones**.


🌀 How It Works Inside
The stator is made up of multiple electromagnetic coils arranged in a circle.

The rotor is a permanent magnet (or has soft iron teeth).

When you energize a coil, it creates a magnetic field that attracts the rotor.

By turning the coils on and off in sequence, you pull the rotor step by step into position.
 ## How my code works
🔄 Stepper Motor in Action
1️⃣ Turn on Coil A → The rotor aligns with Coil A.
2️⃣ Turn off Coil A, turn on Coil B → The rotor moves to align with Coil B.









