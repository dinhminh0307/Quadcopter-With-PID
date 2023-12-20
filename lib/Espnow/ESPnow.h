#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

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

void Init_ESPnow();
void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len);