#include <Arduino.h>

const int lm35Pin = A0;  // LM35 temperature sensor pin
const int ledPin = 13;   // Onboard LED pin

int temperature = 0;     // Variable to store temperature
int blinkInterval = 250; // Initial interval for LED blinking

unsigned long previousMillis = 0; // Variable to store time
bool isLEDOn = false;    // Flag to keep track of LED state

void setup() {
  pinMode(lm35Pin, INPUT); // LM35 pin as input
  pinMode(ledPin, OUTPUT); // LED pin as output
}

void loop() {
  temperature = readTemperature(); // Read temperature from LM35 sensor

  if (temperature < 30) {
    blinkInterval = 250; // Set interval to 250ms if temperature is below 30°C
  } else {
    blinkInterval = 500; // Set interval to 500ms if temperature is above or equal to 30°C
  }

  unsigned long currentMillis = millis(); // Get current time

  if (currentMillis - previousMillis >= blinkInterval) { // Check if it's time to blink the LED
    previousMillis = currentMillis; // Save the last time the LED blinked

    if (isLEDOn) {
      digitalWrite(ledPin, LOW); // Turn off LED
    } else {
      digitalWrite(ledPin, HIGH); // Turn on LED
    }
    
    isLEDOn = !isLEDOn; // Toggle LED state
  }
}

int readTemperature() {
  int sensorValue = analogRead(lm35Pin); // Read sensor value
  float voltage = (sensorValue / 1023.0) * 5.0; // Convert sensor value to voltage
  float temperatureC = (voltage - 0.5) * 100.0; // Convert voltage to temperature in Celsius
  return temperatureC; // Return temperature
}
