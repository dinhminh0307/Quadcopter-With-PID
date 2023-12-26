#include <Arduino.h>
#include "../Espnow/ESPnow.h"
// ================================================================
// Variable declaration
// ================================================================
// The PID object is configured as follows:
// input = sensor, variable to be controller;
// output = pid output, command sent to the motors;
// setpoint = reference setpoint, the desired angle (usually 0deg to maintain an upward position)
// PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

extern double pid_output_x, pid_output_y, pid_output_z, motor_cmd;
// Init gain
extern double kp, ki, kd, anglex_setpoint, angley_setpoint, anglez_setpoint;
extern double gyrox_setpoint, gyroy_setpoint, gyroz_setpoint;
// ================================================================
// Function Definition
// ================================================================
void Init_PID();

void Compute_PID();
void PID_Gyro_Init();// this one to set the setpoint for the angular motor
void PID_Angle_Init(); // this one is to sent the output to motor
void PID_Gyro_Compute();
void PID_Angle_Compute();
void PID_Tunning_Command();