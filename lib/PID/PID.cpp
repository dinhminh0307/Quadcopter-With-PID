#include <PID.h>
#include "../PID_v1/PID_v1.h"
#include <MPU.h>

double pid_output_x = 0, pid_output_y = 0, pid_output_z = 0;
double kp = 5.0, ki = 0.0, kd = 0.0, anglex_setpoint = 0, angley_setpoint = 0, anglez_setpoint = 0;
double gyrox_setpoint = 0, gyroy_setpoint = 0, gyroz_setpoint = 0;

PID myPIDGyroX(&anglex, &gyrox_setpoint, &anglex_setpoint, kp, ki, kd, DIRECT);
PID myPIDGyroY(&angley, &gyroy_setpoint, &angley_setpoint, kp, ki, kd, DIRECT);
PID myPIDGyroZ(&anglez, &gyroz_setpoint, &anglez_setpoint, kp, ki, kd, DIRECT);

PID myPIDAngleX(&gyrox, &pid_output_x, &gyrox_setpoint, kp, ki, kd, DIRECT);
PID myPIDAngleY(&gyroy, &pid_output_y, &gyroy_setpoint, kp, ki, kd, DIRECT);
PID myPIDAngleZ(&gyroz, &pid_output_z, &gyroz_setpoint, kp, ki, kd, DIRECT);

void Init_PID()
{
    myPIDGyroX.SetMode(AUTOMATIC);
    myPIDGyroX.SetOutputLimits(-100, 100);
    myPIDGyroX.SetSampleTime(10);

    myPIDGyroY.SetMode(AUTOMATIC);
    myPIDGyroY.SetOutputLimits(-100, 100);
    myPIDGyroY.SetSampleTime(10);

    myPIDGyroZ.SetMode(AUTOMATIC);
    myPIDGyroZ.SetOutputLimits(-100, 100);
    myPIDGyroZ.SetSampleTime(10);

    myPIDAngleX.SetMode(AUTOMATIC);
    myPIDAngleX.SetOutputLimits(-100, 100);
    myPIDAngleX.SetSampleTime(10);

    myPIDAngleX.SetMode(AUTOMATIC);
    myPIDAngleX.SetOutputLimits(-100, 100);
    myPIDAngleX.SetSampleTime(10);

    myPIDAngleZ.SetMode(AUTOMATIC);
    myPIDAngleZ.SetOutputLimits(-100, 100);
    myPIDAngleZ.SetSampleTime(10);
}

void Compute_PID()
{
    myPIDGyroX.SetTunings(kp, ki, kd);
    myPIDGyroX.Compute();

    myPIDGyroY.SetTunings(kp, ki, kd);
    myPIDGyroY.Compute();

    myPIDGyroZ.SetTunings(kp, ki, kd);
    myPIDGyroZ.Compute();

    myPIDAngleX.SetTunings(kp, ki, kd);
    myPIDAngleX.Compute();

    myPIDAngleY.SetTunings(kp, ki, kd);
    myPIDAngleY.Compute();

    myPIDAngleZ.SetTunings(kp, ki, kd);
    myPIDAngleZ.Compute();

    if (abs(anglex) > 45 || abs(angley) > 45)
    {
        pid_output_x = 0; // motor stop when fall
        pid_output_y = 0;
    }
}