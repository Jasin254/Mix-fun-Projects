# Import required libraries
import RPi.GPIO as GPIO
import time

# Set GPIO mode
GPIO.setmode(GPIO.BCM)

# Define motor pins
leftMotor1 = 2
leftMotor2 = 3
rightMotor1 = 4
rightMotor2 = 5

# Define sensor pins
sensor1 = 0
sensor2 = 1
sensor3 = 2
sensor4 = 3
sensor5 = 4

# Initialize motor pins as outputs
GPIO.setup(leftMotor1, GPIO.OUT)
GPIO.setup(leftMotor2, GPIO.OUT)
GPIO.setup(rightMotor1, GPIO.OUT)
GPIO.setup(rightMotor2, GPIO.OUT)

# Initialize sensor pins as inputs
GPIO.setup(sensor1, GPIO.IN)
GPIO.setup(sensor2, GPIO.IN)
GPIO.setup(sensor3, GPIO.IN)
GPIO.setup(sensor4, GPIO.IN)
GPIO.setup(sensor5, GPIO.IN)

# Define motor control function
def setMotorSpeeds(leftSpeed, rightSpeed):
    GPIO.output(leftMotor1, GPIO.HIGH if leftSpeed > 0 else GPIO.LOW)
    GPIO.output(leftMotor2, GPIO.HIGH if leftSpeed < 0 else GPIO.LOW)
    GPIO.output(rightMotor1, GPIO.HIGH if rightSpeed > 0 else GPIO.LOW)
    GPIO.output(rightMotor2, GPIO.HIGH if rightSpeed < 0 else GPIO.LOW)
    leftSpeed = abs(leftSpeed)
    rightSpeed = abs(rightSpeed)
    GPIO.output(leftMotor1, GPIO.HIGH if leftSpeed > 0 else GPIO.LOW)
    GPIO.output(leftMotor2, GPIO.HIGH if leftSpeed < 0 else GPIO.LOW)
    GPIO.output(rightMotor1, GPIO.HIGH if rightSpeed > 0 else GPIO.LOW)
    GPIO.output(rightMotor2, GPIO.HIGH if rightSpeed < 0 else GPIO.LOW)
    PWM_left.ChangeDutyCycle(leftSpeed)
    PWM_right.ChangeDutyCycle(rightSpeed)

# Initialize PWM pins for motor control
PWM_left = GPIO.PWM(leftMotor1, 100)
PWM_right = GPIO.PWM(rightMotor1, 100)
PWM_left.start(0)
PWM_right.start(0)

# Start the main loop
while True:
    # Read sensor values
    val1 = GPIO.input(sensor1)
    val2 = GPIO.input(sensor2)
    val3 = GPIO.input(sensor3)
    val4 = GPIO.input(sensor4)
    val5 = GPIO.input(sensor5)

    # Determine motor speeds based on sensor values
    leftSpeed = 100
    rightSpeed = 100
    if val1 == 0:
        leftSpeed = 50
    if val5 == 0:
        rightSpeed = 50

    # Set motor speeds
    setMotorSpeeds(leftSpeed, rightSpeed)

    # Wait for a short period
    time.sleep(0.01)
