
#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#define BUTTON_1_PIN 33
#define INTERUPT_STATE 300
#define MIN_SIGNAL 1000
#define MAX_SIGNAL 2000
#define MAX_SIGNAL_STATE 1
#define MIN_SIGNAL_STATE 2

// variable declare

typedef struct voltage_struct_receive
{
    int voltageVal;
} voltage_struct_receive;

typedef struct button_struct_receive
{
    int buttontState;
} button_struct_receive;

typedef struct cal_signal_receive
{
    int signal;
    int state;
} cal_signal_receive;

extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;
extern cal_signal_receive calSignalReceiver;

void rotateBLDC();
void esp_now_config();
void ESC_init();
void droneConfig();
