#include <Arduino.h>
#include "../PID_v1/PID_v1.h"
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
extern double anglex_setpoint, angley_setpoint, anglez_setpoint;
extern double kpX, kiX, kdX;
// pid for y axis
extern double kpY, kiY, kdY;
// pid for z axis
extern double kpZ, kiZ, kdZ;
extern double gyrox_setpoint, gyroy_setpoint, gyroz_setpoint;
// ================================================================
// Function Definition
// ================================================================
void Init_PID();

void Compute_PID();
void PID_Gyro_Init();     // this one to set the setpoint for the angular motor
void PID_Angle_Init();    // this one is to sent the output to motor
void PID_Gyro_Compute();  // compute desired angular velocity to be used as setpoint with PID
void PID_Angle_Compute(); // compute desired motor speed to get that angular velocity setpoint