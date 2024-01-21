#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <MPU.h>
#include <PID.h>

#define YAW_LEFT_STATE 1
#define YAW_RIGHT_STATE 2
#define YAW_NEUTRAL_STATE 0

// Joystick positions
#define JOYSTICK_MIDDLE 5
#define JOYSTICK_MAX    12
#define JOYSTICK_MIN    0

// Setpoint angles
#define ANGLE_FORWARD   -15
#define ANGLE_BACKWARD  15
#define ANGLE_ROLL_RIGHT 20
#define ANGLE_ROLL_LEFT -20
#define ANGLE_HOVER     0
// variable declare

typedef struct voltage_struct_receive
{
    int voltageVal;
} voltage_struct_receive;

typedef struct button_struct_receive
{
    int state;
    int id[25];
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

typedef struct button_struct_send
{
    int state;
    int id[20];
} button_struct_send;

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

typedef struct imu_calibrate_send
{
    int status;
    char id[98];
} imu_calibrate_send;

typedef struct tunning_struct_receive
{
    double kpPitch, kdPitch, kiPitch;
    double kpRoll, kdRoll, kiRoll;
    double kpYaw, kdYaw, kiYaw;
    int tunningState;
} tunning_struct_receive;

typedef struct tunning_struct_send
{
    double kpPitch, kdPitch, kiPitch;
    double kpRoll, kdRoll, kiRoll;
    double kpYaw, kdYaw, kiYaw;
    int tunningState;
} tunning_struct_send;

typedef struct yaw_struct_receive
{
    int yawState;
    char id[45];
} yaw_struct_receive;

extern imu_struct_send imuInfoSender;
extern joystick_struct_receiver joystickSignalReceiver;
extern voltage_struct_receive recieved_Voltage;
extern button_struct_receive received_Button;
extern cal_signal_receive calSignalReceiver;
extern tunning_struct_receive tunningReceiver;
extern button_struct_send buttonSender;
extern int isStop;
extern uint8_t broadcastAddress[];
extern imu_calibrate_send imuCalStatus;
extern yaw_struct_receive yaw_signal_receiver;

void Init_ESPnow();
void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len);
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void setNewPIValue();
void sendPIDValue();
void resetTunning();