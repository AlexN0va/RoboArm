# RoboArm

## INtroduction

Just when I was cleanign out some electrocnics I had, I realized that I had a pwm servo driver. I don't knwo where how it got in my electronics box, but with that my journey began on bulindg a robot arm with some servos and stepper motor. I've been wanting to create a robot arm for a long time,a dn thsi will be a ever gogin project, but we will begin with this v1 of RoboArm. 

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







