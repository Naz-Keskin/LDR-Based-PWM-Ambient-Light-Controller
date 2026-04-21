// LDR-Based PWM Ambient Light Controller
// Author: Naz | TOBB ETU - Electrical and Electronics Engineering

// --- Hardware Pin Definitions ---
const int ldrPin = A0;   // Analog input pin for the LDR voltage divider
const int ledPin = 9;    // Digital output pin (PWM supported)

void setup() {
  pinMode(ledPin, OUTPUT); // Configure LED pin as output
  
  // Initialize serial communication for real-time sensor calibration
  Serial.begin(9600); 
}

void loop() {
  // 1. Sample Analog Data
  int sensorValue = analogRead(ldrPin);
  
  // 2. Signal Processing (Mapping)
  // Map the specific ambient light range (450-750) to the 8-bit PWM resolution (0-255).
  // Note: Adjust the '450' (light) and '750' (dark) values based on current room conditions.
  int brightness = map(sensorValue, 450, 750, 0, 255);
  
  // 3. Safety Constraint
  // Ensure the processed value does not overflow the 8-bit boundary (0-255)
  brightness = constrain(brightness, 0, 255);
  
  // 4. Output Generation
  // Send the computed PWM duty cycle to the LED
  analogWrite(ledPin, brightness);
  
  // 5. Debugging Output
  Serial.print("Sensor ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | PWM Output: ");
  Serial.println(brightness);
  
  // Minimal delay to stabilize the ADC readings
  delay(30);
}
