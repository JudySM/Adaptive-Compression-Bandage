const int forceSensorPin = A0;  // Analog pin A0 is connected to the force sensor

void setup() {
  Serial.begin(9600);           // Initialize serial communication
}

void loop() {
  // Read the analog value from the force sensor
  int sensorValue = analogRead(forceSensorPin);

  // Convert analog reading to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert voltage to pressure (mmHg) based on calibration factor
  float pressure_mmHg = convertToPressure(voltage);

  // Print the pressure value
  Serial.print("Pressure (mmHg): ");
  Serial.println(pressure_mmHg);

  delay(500);  // Delay to stabilize readings
}

// Function to convert voltage to pressure (calibrate this factor)
float convertToPressure(float voltage) {
  // Placeholder conversion factor; adjust after calibration
  float pressure = voltage * 12;
  return pressure;
}