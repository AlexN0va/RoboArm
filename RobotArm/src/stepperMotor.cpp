#include "stepperMotor.h"
#include <Arduino.h>
#include <Stepper.h>

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 2048;

// ULN2003 Motor Driver Pins
#define IN1 27
#define IN2 14
#define IN3 12
#define IN4 13

// Initialize the stepper library with the motor driver pins
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

volatile bool motorRunning = false;
volatile int motorDirection = 0; // 1 = forward, -1 = backward, 0 = stop


// Function to initialize the motor
void startMotor() {
    myStepper.setSpeed(5);
    Serial.println("Stepper motor initialized.");
}

void startForward() {
    Serial.println("Starting forward movement...");
    // Start moving the motor forward continuously
    motorRunning = true;
    motorDirection = 1;
}

void startBackward() {
    Serial.println("Starting backward movement...");
    // Start moving the motor backward continuously
    motorRunning = true;
    motorDirection = -1;
}

void stopMotor() {
    Serial.println("Stopping motor...");
    // Stop the motor
    motorRunning = false;
    motorDirection = 0;
}

void handleMotorMovement() {
    if (motorRunning) {
        if (motorDirection == 1) {
            myStepper.step(1); // Move one step forward
        } else if (motorDirection == -1) {
            myStepper.step(-1); // Move one step backward
        }
    }
}