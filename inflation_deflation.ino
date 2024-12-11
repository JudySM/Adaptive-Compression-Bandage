#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

// Pin assignments for the pumps
const int inflationPin = 9;  // Pin to control the inflation pump
const int deflationPin = 10; // Pin to control the deflation pump

PulseOximeter pox;
uint32_t tsLastReport = 0;
bool cuffInflated = false;

// Callback for beat detection
void onBeatDetected() {
    Serial.println("Beat detected!");
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the pulse oximeter
  Serial.print("Initializing MAX30100 sensor...");
  if (!pox.begin()) {
    Serial.println("Failed to initialize MAX30100. Check the sensor connection.");
    while (1);
  } else {
    Serial.println("Sensor initialized successfully.");
  }

  // Set callback for beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // Set pump pins as output
  pinMode(inflationPin, OUTPUT);
  pinMode(deflationPin, OUTPUT);

  // Ensure pumps are off at the start
  digitalWrite(inflationPin, LOW);
  digitalWrite(deflationPin, LOW);

  // Inflate the cuff for 10 seconds initially
  inflateCuff();
}

void loop() {
  // Continuously update the pulse oximeter sensor
  pox.update();

  // Report heart rate every second
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();

    // Get the current BPM value
    float BPM = pox.getHeartRate();
    Serial.print("BPM: ");
    Serial.println(BPM);

    // Check if heart rate is valid
    if (BPM > 0) {
      // If BPM drops below 60 and the cuff is inflated, deflate the cuff
      if (BPM < 60 && cuffInflated) {
        Serial.println("BPM is below 60. Deflating the cuff.");
        deflateCuff();
      }
    } else {
      Serial.println("Invalid BPM. Waiting for valid reading...");
    }
  }
}

// Function to inflate the cuff
void inflateCuff() {
  Serial.println("Inflating the cuff for 10 seconds...");
  digitalWrite(inflationPin, HIGH);  // Turn on inflation pump
  delay(10000);                      // Keep the pump running for 10 seconds
  digitalWrite(inflationPin, LOW);   // Turn off inflation pump
  cuffInflated = true;               // Mark cuff as inflated
}

// Function to deflate the cuff
void deflateCuff() {
  Serial.println("Deflating the cuff...");
  digitalWrite(deflationPin, HIGH);  // Turn on deflation pump
  delay(5000);                       // Run deflation pump for 5 seconds
  digitalWrite(deflationPin, LOW);   // Turn off deflation pump
  cuffInflated = false;              // Mark cuff as deflated
}