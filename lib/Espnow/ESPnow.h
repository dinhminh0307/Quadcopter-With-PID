#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <MPU.h>
#include <PID.h>

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


typedef struct imu_struct_send
{
    float anglex; // Angle in the X direction
    float angley; // Angle in the Y direction
    float anglez; // Angle in the Z direction
    float gyrox;  // Gyroscope reading in the X direction
    float gyroy;  // Gyroscope reading in the Y direction
    float gyroz;  // Gyroscope reading in the Z direction
    int motor1Speed;
    int motor2Speed;
    int motor3Speed;
    int motor4Speed;
    int baseSpeedSend;
} imu_struct_send;

typedef struct tunning_struct_receive {
    float kpPitch,kdPitch,kiPitch;
    float kpRoll,kdRoll,kiRoll;
    float kpYaw,kdYaw,kiYaw;
} tunning_struct_receive;


extern imu_struct_send imuInfoSender;
extern joystick_struct_receiver joystickSignalReceiver;
extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;
extern cal_signal_receive calSignalReceiver;
extern tunning_struct_receive tunningReceiver;
extern uint8_t broadcastAddress[];


void Init_ESPnow();
void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len);
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void resetTunning();