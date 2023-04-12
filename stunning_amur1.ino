#include <Servo.h>

// Pins for the ultrasonic sensor
const int triggerPin = 7;
const int echoPin = 6;

// Pin for the servo motor
const int servoPin = 3;

// Pins for SoftwareSerial
const int receivePin = 11;
const int transmitPin = 12;

// Door positions (in degrees)
const int doorOpenPosition = 0;
const int doorClosedPosition = 90;

// Distance threshold for the mouse (in cm)
const int mouseDetectionThreshold = 5;

// Initialize the Servo object
Servo doorServo;

void setup() {
  // Set the ultrasonic sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo to the servo pin
  doorServo.attach(servoPin);

  // Set the initial door position
  doorServo.write(doorOpenPosition);

  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure the distance using the ultrasonic sensor
  int distanceToMouse = measureDistance();

  // Check if the distance is less than the threshold
  if (distanceToMouse <= mouseDetectionThreshold) {
    // Close the door
    doorServo.write(doorClosedPosition);

    // Send signal to the reset system Arduino
    Serial.write('a');

    // Stop checking for the mouse, keeping the door closed
    while (true) {
      if (Serial.available()) {
        char command = Serial.read();
        if (command == 'b') {
          // Open the door and resume normal operation
          doorServo.write(doorOpenPosition);
          break;
        }
      }
    }
  }
}

int measureDistance() {
  // Clear the triggerPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the triggerPin high for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the echoPin, which returns the travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  int distance = duration * 0.0344 / 2;

  return distance;
}