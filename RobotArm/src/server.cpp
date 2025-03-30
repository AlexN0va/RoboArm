#include "server.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "stepperMotor.h" // Include motor control functions
#include "servoMotor.h"   // Include servo control functions

const char* ssid = "Liam";
const char* password = "Liam1965";

AsyncWebServer server(80); // Use AsyncWebServer instead of WebServer

// Function to serve the HTML file
void handleRoot(AsyncWebServerRequest *request) {
    request->send(200, "text/html", R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>ESP32 Motor & Servo Control</title>
            <style>
                body { font-family: Arial, sans-serif; text-align: center; }
                .slider-container { margin: 20px; }
                input[type=range] { width: 80%; }
            </style>
        </head>
        <body>
            <h1>ESP32 Stepper & Servo Control</h1>

            <!-- Stepper Motor Buttons -->
            <button 
                onmousedown="fetch('/startForward')"
                onmouseup="fetch('/stop')"
                ontouchstart="fetch('/startForward')"
                ontouchend="fetch('/stop')">
                Move Forward
            </button>

            <button 
                onmousedown="fetch('/startBackward')"
                onmouseup="fetch('/stop')"
                ontouchstart="fetch('/startBackward')"
                ontouchend="fetch('/stop')">
                Move Backward
            </button>

            <h2>Servo Control</h2>

            <div class="slider-container">
                <label>Servo 1:</label>
                <input type="range" min="0" max="180" value="90" id="servo1" oninput="updateServo(1, this.value)">
            </div>

            <div class="slider-container">
                <label>Servo 2:</label>
                <input type="range" min="0" max="180" value="90" id="servo2" oninput="updateServo(2, this.value)">
            </div>

            <div class="slider-container">
                <label>Servo 3:</label>
                <input type="range" min="0" max="180" value="90" id="servo3" oninput="updateServo(3, this.value)">
            </div>

            <script>
                function updateServo(servo, value) {
                    fetch(`/setServo?servo=${servo}&value=${value}`)
                        .then(response => console.log(`Servo ${servo} moved to ${value}`));
                }
            </script>
        </body>
        </html>
    )rawliteral");
}

// Handle undefined routes
void handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "404: Not Found");
}

// Web server setup
void startServer() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Serial monitor output
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    startMotor();  // Initialize motor
    startServo();  // Initialize servo

    // Main Webpage Route
    server.on("/", HTTP_GET, handleRoot);

    // Stepper motor control routes
    server.on("/startForward", HTTP_GET, [](AsyncWebServerRequest *request) {
        startForward(); // Call the function to move the motor forward
        request->send(200); // Send an empty response
    });

    server.on("/startBackward", HTTP_GET, [](AsyncWebServerRequest *request) {
        startBackward(); // Call the function to move the motor backward
        request->send(200); // Send an empty response
    });

    server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request) {
        stopMotor(); // Call the function to stop the motor
        request->send(200); // Send an empty response
    });

    // Servo Routes
    server.on("/setServo", HTTP_GET, handleServoRequest);

    server.onNotFound(handleNotFound); // Handle undefined routes

    server.begin();
}
