#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H
#include <ESPAsyncWebServer.h>


void startServo();
void setServoPosition(int servoNum, int angle);
void handleServoRequest(AsyncWebServerRequest *request);


#endif