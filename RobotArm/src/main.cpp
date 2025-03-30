#include <Arduino.h>
#include "server.h"
#include "StepperMotor.h"

void setup() {
    Serial.begin(115200); //initialize Serial Monitor
    startServer(); // Start the web server
}

void loop() {
    handleMotorMovement(); // Handle motor movement
    //process the http requests and send appropriate response
}

