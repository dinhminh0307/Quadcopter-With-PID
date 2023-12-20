#include <PID.h>
#include "../PID_v1/PID_v1.h"
#include <MPU.h>

double pid_output = 0, motor_cmd = 127;
double kp = 5.0, ki = 0.0, kd = 0.0, anglex_setpoint = 0;

PID myPID(&anglex, &pid_output, &anglex_setpoint, kp, ki, kd, DIRECT);

void Init_PID()
{
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-127, 127);
    myPID.SetSampleTime(10);
}

void Compute_PID()
{
    myPID.SetTunings(kp, ki, kd);
    myPID.Compute();
    if (abs(anglex) > 30)
        pid_output = 0; // motor stop when fall
    motor_cmd = map(pid_output, -127, 127, 0, 255);
}