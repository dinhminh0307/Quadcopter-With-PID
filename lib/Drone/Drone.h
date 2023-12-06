#ifndef DRONE_H
#define DRONE_H
#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#define BUTTON_1_PIN 33
#define INTERUPT_STATE 300

// variable declare

typedef struct voltage_struct_receive {
    int voltageVal;
} voltage_struct_receive;

typedef struct button_struct_receive {
    int buttontState;
} button_struct_receive;

extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;

void rotateBLDC();
void esp_now_config();
void ESC_init();
void droneConfig();
#endif