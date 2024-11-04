/*
MIT License
Author: Kerogs
Last Modified: 04/11/2024
Project URL: https://github.com/kerogs/doorAutoLight
GitHub Profile: https://github.com/kerogs/
Version: 1
*/

#include <Servo.h>

// Pin configuration
#define SERVO_PIN 3         // Servo motor control pin
#define ECHO_PIN 8          // Ultrasonic sensor echo pin
#define TRIG_PIN 9          // Ultrasonic sensor trigger pin
#define LED_INDICATOR_PIN 4 // Indicator LED pin

// Distance and timing settings (modifiable)
int maxDistance = 10;      // Maximum detection distance in cm
int durationAction = 3000; // Activation duration in milliseconds

// Global variables
long duration, distance;

// Servo motor instance
Servo servo;

void setup() {
  // Initialize servo
  servo.attach(SERVO_PIN);
  servo.write(0); // Initial position

  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LED indicator
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_INDICATOR_PIN, LOW); // LED off by default
}

void loop() {
  delay(1000); // Main loop delay

  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read pulse duration and convert to distance in cm
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58.2;

  // Check if distance is within threshold
  if (distance > maxDistance) {
    // Activate servo and LED
    servo.write(180);
    delayMicroseconds(60); // Short delay for servo movement
    servo.write(0);        // Reset servo position
    digitalWrite(LED_INDICATOR_PIN, HIGH); // Turn on LED

    delay(durationAction); // Wait for specified activation duration

    // Deactivate servo and LED
    servo.write(180);
    delayMicroseconds(60);
    servo.write(0);
    digitalWrite(LED_INDICATOR_PIN, LOW); // Turn off LED
  }
}
