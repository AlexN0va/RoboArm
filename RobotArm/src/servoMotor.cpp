#include <Wire.h>
#include "ServoMotor.h"
#include <Adafruit_PWMServoDriver.h>


// PCA9685 Setup
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Servo pulse limits
#define SERVO_MIN  150  // Min pulse length
#define SERVO_MAX  600  // Max pulse length

// Servo Channels
#define POS_SERVO1_CHANNEL 7
#define POS_SERVO2_CHANNEL 8
#define POS_SERVO3_CHANNEL 12

void startServo(){
    pwm.begin();
    pwm.setPWMFreq(50);  // Set frequency to 50 Hz for servos
    Serial.println("PCA9685 Initialized.");
}

void setServoPosition(int servoNum, int angle) {
    int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);

    switch (servoNum) {
        case 1:
            pwm.setPWM(POS_SERVO1_CHANNEL, 0, pulse);
            break;
        case 2:
            pwm.setPWM(POS_SERVO2_CHANNEL, 0, pulse);
            break;
        case 3:
            pwm.setPWM(POS_SERVO3_CHANNEL, 0, pulse);
            break;
        default:
            break;
    }
}

void handleServoRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("servo") && request->hasParam("value")) {
        int servoNum = request->getParam("servo")->value().toInt();
        int value = request->getParam("value")->value().toInt();
        
        setServoPosition(servoNum, value);
        request->send(200, "text/plain", "Servo updated");
    } else {
        request->send(400);
    }
}