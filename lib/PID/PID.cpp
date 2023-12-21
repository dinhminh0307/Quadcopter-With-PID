#include <PID.h>
#include "../PID_v1/PID_v1.h"
#include <MPU.h>

double pid_output_x = 0, pid_output_y = 0, pid_output_z = 0;
double kp = 5.0, ki = 0.0, kd = 0.0, anglex_setpoint = 0, angley_setpoint = 0, anglez_setpoint = 0;
double gyrox_setpoint = 0, gyroy_setpoint = 0, gyroz_setpoint = 0;

PID myPIDx(&anglex, &pid_output_x, &anglex_setpoint, kp, ki, kd, DIRECT);
PID myPIDy(&angley, &pid_output_y, &angley_setpoint, kp, ki, kd, DIRECT);
PID myPIDz(&anglez, &pid_output_z, &anglez_setpoint, kp, ki, kd, DIRECT);

void Init_PID()
{
    myPIDx.SetMode(AUTOMATIC);
    myPIDx.SetOutputLimits(0, 90);
    myPIDx.SetSampleTime(10);

    myPIDy.SetMode(AUTOMATIC);
    myPIDy.SetOutputLimits(0, 90);
    myPIDy.SetSampleTime(10);

    myPIDz.SetMode(AUTOMATIC);
    myPIDz.SetOutputLimits(0, 90);
    myPIDz.SetSampleTime(10);
}

void Compute_PID()
{
    myPIDx.SetTunings(kp, ki, kd);
    myPIDx.Compute();

    myPIDy.SetTunings(kp, ki, kd);
    myPIDy.Compute();

    myPIDz.SetTunings(kp, ki, kd);
    myPIDz.Compute();

    if (abs(anglex) > 45 || abs(angley) > 45)
    {
        pid_output_x = 0; // motor stop when fall
        pid_output_y = 0;
    }
}