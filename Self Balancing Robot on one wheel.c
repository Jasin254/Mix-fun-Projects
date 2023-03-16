#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

#define MOTOR_PIN 0
#define MOTOR_PWM_RANGE 100

#define TARGET_ANGLE 0.0
#define K_P 30.0
#define K_I 0.0
#define K_D 20.0
#define DT 0.01

int fd;

float AccelX, AccelY, AccelZ, GyroX, GyroY, GyroZ;
float AccelAngleX, AccelAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
float FilteredAngleX, AngleX, Error, PTerm, ITerm, DTerm, PID;
float PreviousError = 0.0, TotalError = 0.0;

void initMPU6050() {
    wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07);
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);
    wiringPiI2CWriteReg8(fd, CONFIG, 0);
    wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);
    wiringPiI2CWriteReg8(fd, ACCEL_CONFIG, 0);
}

void readMPU6050() {
    AccelX = wiringPiI2CReadReg16(fd, ACCEL_XOUT_H);
    AccelY = wiringPiI2CReadReg16(fd, ACCEL_YOUT_H);
    AccelZ = wiringPiI2CReadReg16(fd, ACCEL_ZOUT_H);
    GyroX = wiringPiI2CReadReg16(fd, GYRO_XOUT_H);
    GyroY = wiringPiI2CReadReg16(fd, GYRO_YOUT_H);
    GyroZ = wiringPiI2CReadReg16(fd, GYRO_ZOUT_H);
}

float getAccelAngleX() {
    return atan(AccelY / sqrt(pow(AccelX, 2) + pow(AccelZ, 2))) * 180.0 / M_PI;
}

float getAccelAngleY() {
    return atan(-1 * AccelX / sqrt(pow(AccelY, 2) + pow(AccelZ, 2))) * 180.0 / M_PI;
}

void updateAngleX() {
    GyroAngleX = GyroAngleX + GyroX * DT;
    GyroAngleY = GyroAngleY + GyroY * DT;
    GyroAngleZ = GyroAngleZ + GyroZ * DT;
    AccelAngleX = getAccelAngleX();
    AngleX = 0.
// Complementary Filter
FilteredAngleX = 0.98 * (FilteredAngleX + GyroX * DT) + 0.02 * AccelAngleX;
// Error Calculation
Error = TARGET_ANGLE - FilteredAngleX;
// PID Calculation
PTerm = K_P * Error;
ITerm += K_I * Error * DT;
DTerm = K_D * (Error - PreviousError) / DT;
TotalError = PTerm + ITerm + DTerm;
PreviousError = Error;
PID = TotalError;
}

void initMotor() {
pinMode(MOTOR_PIN, PWM_OUTPUT);
softPwmCreate(MOTOR_PIN, 0, MOTOR_PWM_RANGE);
}

void setMotorSpeed(float speed) {
if (speed > 1.0) {
speed = 1.0;
}
if (speed < -1.0) {
speed = -1.0;
}
if (speed >= 0.0) {
softPwmWrite(MOTOR_PIN, (int)(speed * MOTOR_PWM_RANGE));
} else {
softPwmWrite(MOTOR_PIN, 0);
delay(100);
softPwmWrite(MOTOR_PIN, (int)(-1.0 * speed * MOTOR_PWM_RANGE));
}
}

int main() {
if (wiringPiSetup() == -1) {
printf("wiringPiSetup failed\n");
return 0;
}
fd = wiringPiI2CSetup(MPU6050_ADDRESS);
initMPU6050();
initMotor();
while (1) {
readMPU6050();
updateAngleX();
setMotorSpeed(PID);
delay(10);
}
return 0;
}

vbnet
Copy code

