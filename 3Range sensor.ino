#define trigPin1 13
#define echoPin1 12

#define trigPin2 11
#define echoPin2 10

#define trigPin3 9
#define echoPin3 8

#define motorPin1 5
#define motorPin2 6
#define motorPin3 7
#define motorPin4 8

void setup() {
  // initialize the pins for the ultrasonic sensors
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  // initialize the pins for the motors
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  // read the distance from the ultrasonic sensors
  long duration1, duration2, duration3;
  int distance1, distance2, distance3;
  
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 / 58;
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 / 58;
  
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 / 58;
  
  // decide the direction and adjust the motor speed accordingly
  // write code for robot movement and obstacle avoidance
  
  // control the robot's arm for picking and placing items
  
  // continue the loop
}
 
