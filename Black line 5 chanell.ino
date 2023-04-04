// Define motor pins
int leftMotor1 = 2;
int leftMotor2 = 3;
//rev
int rightMotor1 = 4;
int rightMotor2 = 5;

// Define sensor pins
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;

void setup() {
  // Initialize motor pins as outputs
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  // Initialize sensor pins as inputs
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
}

void loop() {
  // Read sensor values
  int val1 = analogRead(sensor1);
  int val2 = analogRead(sensor2);
  int val3 = analogRead(sensor3);
  int val4 = analogRead(sensor4);
  int val5 = analogRead(sensor5);

  // Determine motor speeds based on sensor values
  int leftSpeed = 100;
  int rightSpeed = 100;
  if (val1 < 500) {
    leftSpeed = 50;
  }
  if (val5 < 500) {
    rightSpeed = 50;
  }

  // Set motor speeds
  analogWrite(leftMotor1, leftSpeed);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, rightSpeed);
  analogWrite(rightMotor2, 0);
}
