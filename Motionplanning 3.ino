#include <Servo.h>

// Define ultrasonic sensor pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;

// Define servo motor pins
const int servoPin = 9;

// Define distance thresholds
const int maxDistance = 100; // Maximum distance (in cm)
const int minDistance = 30; // Minimum distance (in cm)

// Define servo angle limits
const int maxAngle = 180; // Maximum angle (in degrees)
const int minAngle = 0; // Minimum angle (in degrees)

// Create servo object
Servo myservo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize servo
  myservo.attach(servoPin);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  // Read distance from ultrasonic sensors
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  int distance3 = getDistance(trigPin3, echoPin3);

  // Determine action based on distances
  if (distance1 < minDistance || distance2 < minDistance || distance3 < minDistance) {
    // Obstacle detected, stop and turn
    stop();
    turn();
  } else if (distance1 < maxDistance && distance2 < maxDistance && distance3 < maxDistance) {
    // No obstacles detected, move forward
    moveForward();
  } else {
    // Obstacle detected on one side, turn in that direction
    if (distance1 < maxDistance) {
      turnLeft();
    } else if (distance3 < maxDistance) {
      turnRight();
    } else {
      // No obstacles detected on sides, move forward
      moveForward();
    }
  }
}

// Function to get distance from an ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  // Send a pulse to the sensor to start the measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the pulse from the sensor
  int duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  int distance = duration / 58;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Function to stop the robot
void stop() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

// Function to turn the robot left
void turnLeft() {
  myservo.write(minAngle);
  delay(500);
}

// Function to turn the robot right
void turnRight() {
  myservo.write(maxAngle);
  delay(500);
}

// Function to turn the robot
void turn
() {
// Stop the robot
stop();

// Choose a random direction to turn
int direction = random(2);

// Turn left or right
if (direction == 0) {
turnLeft();
} else {
turnRight();
}
}
