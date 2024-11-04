/*
MIT License
Author: Kerogs
Last Modified: 04/11/2024
Project URL: https://github.com/kerogs/doorAutoLight
GitHub Profile: https://github.com/kerogs/
Version: 2
*/

#include <Servo.h>

// Pin configuration
#define SERVO_PIN 3         // Servo motor control pin
#define ECHO_PIN 8          // Ultrasonic sensor echo pin
#define TRIG_PIN 9          // Ultrasonic sensor trigger pin
#define LED_INDICATOR_PIN 4 // Indicator LED pin

// Action information
bool actionStatus = false;

// Distance and timing settings (modifiable)
int maxDistance = 10;      // Maximum detection distance in cm
int durationAction = 8000; // The time that elapses before the Servo presses again. (ms)
int delayServoBetweenAction = 1000; // Delay between servo movement and return to initial position. (ms)
int servoAngleMax = 180;  // Servo stop angle (180° max) (deg)

// Global variables
long duration, distance;

// myServo motor instance
Servo myServo;

void setup() {
  // Initialize myServo
  myServo.attach(SERVO_PIN);
  myServo.write(0); // Initial position

  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LED indicator
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_INDICATOR_PIN, LOW); // LED off by default

  Serial.begin(9600);
  Serial.print("ok");

  actionStatus = false;
}

void loop() {
  delay(1000); // Main loop delay
  Serial.println("Check...");

  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read pulse duration and convert to distance in cm
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58.2;
  Serial.print("Distance : "); Serial.print(distance); Serial.println("cm");

  // Check if distance is within threshold
  if (distance > maxDistance && !actionStatus) {
    Serial.println("maxDistance ! StartAction");

    Serial.println("Set light : ON");
    // Activate myServo and LED
    myServo.write(180);
    delay(delayServoBetweenAction); // Short delay for myServo movement
    myServo.write(0);        // Reset myServo position
    digitalWrite(LED_INDICATOR_PIN, HIGH); // Turn on LED

    Serial.print("Delay light ON : "); Serial.print(durationAction); Serial.println("ms");
    delay(durationAction); // Wait for specified activation duration

    // Deactivate myServo and LED
    Serial.println("Set light : OFF");
    myServo.write(180);
    delay(delayServoBetweenAction);
    myServo.write(0);
    digitalWrite(LED_INDICATOR_PIN, LOW); // Turn off LED

    actionStatus = true;
  }

  if(distance < maxDistance){
    actionStatus = false;
    myServo.write(0);
  }
}