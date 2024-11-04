# doorAutoLight
code with an ultrasonic sensor. Which detects when a door is opened and switches on the light.

## dal-s.ino
Version of the code that works with a servo motor that turns to press a button.

### required electronic component
- Arduino
- Motor servo
- ultrasonic sensor
- led (optional)
    - 220Ω resistor (optional)

### Library
- Servo.h

### Variable to change
```cpp
// Distance and timing settings (modifiable)
int maxDistance = 10;      // Maximum detection distance in cm
int durationAction = 8000; // The time that elapses before the Servo presses again. (ms)
int delayServoBetweenAction = 1000; // Delay between servo movement and return to initial position. (ms)
int servoAngleMax = 180;  // Servo stop angle (180° max) (deg)
```

### Schema
![alt text](.ksinf/dal-s.png)