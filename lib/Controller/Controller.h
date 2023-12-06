#if 0
#include <ESP32Servo.h>
#include <esp32_button.h>
#include <esp_now.h>
#include <WiFi.h>
#define BUTTON_1_PIN 33
#define INTERUPT_VAL 200

extern button_t button_1;

typedef struct button_message {
    int button_status;
} button_message;

typedef struct voltage_stuct {
    int voltageVal;
} voltage_stuct;



void esp_now_config();
void buttonInit();
void remoteControllerConfig();
void potentiometerSend(int myVal);
void buttonDataSend(int myVal);
void buttonPressed(int val);
int ADC_Read();
#endif