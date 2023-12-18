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

typedef struct min_signal_receiv{
    int minSignal;
    bool state;
} min_signal_receive;

typedef struct max_signal_receive {
    int maxSignal;
    bool state;
    bool status;
} max_signal_receive;

extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;
extern min_signal_receive minSignalReceiver;
extern max_signal_receive maxSignalReceiver;

void rotateBLDC();
void esp_now_config();
void ESC_init();
void droneConfig();
#endif