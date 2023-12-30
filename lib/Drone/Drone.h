
#include <ESP32Servo.h>
#include <esp_now.h>
#include <PID.h>

#define ESC_PWM 32
#define ESC_PWM2 25
#define ESC_PWM3 26
#define ESC_PWM4 33
// 32 26 cc 25 33 cw
// 32 25 pitch back 33 26 pitch front
// 25 26 roll right
// 32 33 roll left
// 25 33 yaw left 32 26 yaw right

#define BUTTON_1_PIN 33
#define INTERUPT_STATE 300
#define MIN_SIGNAL 1000
#define MAX_SIGNAL 2000
#define MAX_SIGNAL_STATE 1
#define MIN_SIGNAL_STATE 2
#define YAW_LEFT 1
#define YAW_RIGHT 2

extern double motor_cmd;
extern int motorSpeed1,motorSpeed2,motorSpeed3,motorSpeed4; // these must be global to easily changed when pitch, roll

void droneHovering();
void esp_now_config();
void Init_ESC();
void applyPitch();
void rotateBLDC(); // this function used in every movement of the drone(hover,pitch, roll, yaw), it contains the logic to turn 4 motor