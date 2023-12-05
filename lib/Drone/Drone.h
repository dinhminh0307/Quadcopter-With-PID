#ifndef DRONE_H
#define DRONE_H
#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#define BUTTON_1_PIN 33
#define INTERUPT_STATE 300

Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int val;
int escPWM = 18;
int escPWM2 = 19;
// int escPWM3 = 33;
int escPWM4 = 25;

typedef struct voltage_struct_receive {
    int voltageVal;
} voltage_struct_receive;

typedef struct button_struct_receive {
    int buttontState;
} button_struct_receive;

voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;

void rotateBLDC();
void esp_now_config();
void ESC_init();
void droneConfig();
#endif