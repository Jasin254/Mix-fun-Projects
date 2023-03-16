#include <wiringPi.h>
#include <softPwm.h>

#define FLAP1_PIN 0 // PWM Pin for flap servo 1
#define FLAP2_PIN 1 // PWM Pin for flap servo 2
#define HEAD_PIN 2  // PWM Pin for head servo
#define TAIL_PIN 3  // PWM Pin for tail servo

#define FLAP_ANGLE 30   // Flapping angle in degrees
#define HEAD_ANGLE 15   // Head angle in degrees
#define TAIL_ANGLE -10  // Tail angle in degrees

#define FLAP_FREQ 25   // Flapping frequency in Hz
#define HEAD_FREQ 50   // Head frequency in Hz
#define TAIL_FREQ 100  // Tail frequency in Hz

void flap(int flap1_angle, int flap2_angle) {
    softPwmWrite(FLAP1_PIN, flap1_angle);
    softPwmWrite(FLAP2_PIN, flap2_angle);
}

void head(int angle) {
    softPwmWrite(HEAD_PIN, angle);
}

void tail(int angle) {
    softPwmWrite(TAIL_PIN, angle);
}

int main() {
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed\n");
        return 0;
    }
    pinMode(FLAP1_PIN, PWM_OUTPUT);
    pinMode(FLAP2_PIN, PWM_OUTPUT);
    pinMode(HEAD_PIN, PWM_OUTPUT);
    pinMode(TAIL_PIN, PWM_OUTPUT);
    softPwmCreate(FLAP1_PIN, 0, 180);
    softPwmCreate(FLAP2_PIN, 0, 180);
    softPwmCreate(HEAD_PIN, 0, 180);
    softPwmCreate(TAIL_PIN, 0, 180);
    while (1) {
        flap(FLAP_ANGLE, -FLAP_ANGLE);
        head(HEAD_ANGLE);
        tail(TAIL_ANGLE);
        delay(1000 / FLAP_FREQ);
        flap(-FLAP_ANGLE, FLAP_ANGLE);
        head(-HEAD_ANGLE);
        tail(-TAIL_ANGLE);
        delay(1000 / FLAP_FREQ);
    }
    return 0;
}
