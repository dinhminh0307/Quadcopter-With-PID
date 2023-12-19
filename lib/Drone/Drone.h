
#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#define BUTTON_1_PIN 33
#define INTERUPT_STATE 300
#define MIN_SIGNAL 1000
#define MAX_SIGNAL 2000
#define MAX_SIGNAL_STATE 1
#define MIN_SIGNAL_STATE 2
#define YAW_LEFT 1
#define YAW_RIGHT 2

// variable declare

typedef struct voltage_struct_receive
{
    int voltageVal;
} voltage_struct_receive;

typedef struct button_struct_receive
{
    int state;
    char id[20];
} button_struct_receive;

typedef struct cal_signal_receive
{
    int signal;
    int state;
} cal_signal_receive;

typedef struct joystick_struct_receiver
{
    int x;
    int y;
    char id[10];
} joystick_struct_receiver;

extern joystick_struct_receiver joystickSignalReceiver;
extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;
extern cal_signal_receive calSignalReceiver;

void rotateBLDC();
void esp_now_config();
void ESC_init();
void droneConfig();
