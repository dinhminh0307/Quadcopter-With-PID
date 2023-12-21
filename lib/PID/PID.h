#include <Arduino.h>

// ================================================================
// Variable declaration
// ================================================================
// The PID object is configured as follows:
// input = sensor, variable to be controller;
// output = pid output, command sent to the motors;
// setpoint = reference setpoint, the desired angle (usually 0deg to maintain an upward position)
// PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

extern double pid_output, motor_cmd;
// Init gain
extern double kp, ki, kd, anglex_setpoint;

// ================================================================
// Function Definition
// ================================================================
void Init_PID();

void Compute_PID();