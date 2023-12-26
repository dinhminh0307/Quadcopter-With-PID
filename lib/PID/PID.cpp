#include <PID.h>
#include "../PID_v1/PID_v1.h"
#include <MPU.h>
#include <string.h>

double pid_output_x = 0, pid_output_y = 0, pid_output_z = 0;
double kp = 5.0, ki = 0.0, kd = 0.0, anglex_setpoint = 0, angley_setpoint = 0, anglez_setpoint = 0;
double gyrox_setpoint = 0, gyroy_setpoint = 0, gyroz_setpoint = 0;
/*to control the angle setpoint, it means that we need to control the angular velocity to stay at that setpoint
- Then that angular velocity will be gotten by controlling the speed of motor (cmd_send_motor)
Formula: angle -> v -> motor command*/
PID PIDgyroX(&anglex, &gyrox_setpoint, &anglex_setpoint, kp, ki, kd, DIRECT);
PID PIDgyroY(&angley, &gyroy_setpoint, &angley_setpoint, kp, ki, kd, DIRECT);
PID PIDgyroZ(&anglez, &gyroz_setpoint, &anglez_setpoint, kp, ki, kd, DIRECT);

PID PIDangleX(&gyrox, &pid_output_x, &gyrox_setpoint, kp, ki, kd, DIRECT);
PID PIDangleY(&gyroy, &pid_output_y, &gyroy_setpoint, kp, ki, kd, DIRECT);
PID PIDangleZ(&gyroz, &pid_output_z, &gyroz_setpoint, kp, ki, kd, DIRECT);

void PID_Gyro_Init() {
    // if the current angle is below 45 => the desired angular vel is blew current angle, else 
    if(abs(anglex) <= 45) {
        PIDgyroX.SetMode(AUTOMATIC);
        PIDgyroX.SetOutputLimits(0, anglex);
        PIDgyroX.SetSampleTime(10);
    }
    else {
        PIDgyroX.SetMode(AUTOMATIC);
        PIDgyroX.SetOutputLimits(0, 45);
        PIDgyroX.SetSampleTime(10);
    }
    
    if(abs(angley) <= 45) {
        PIDgyroY.SetMode(AUTOMATIC);
        PIDgyroY.SetOutputLimits(0, angley);
        PIDgyroY.SetSampleTime(10);
    }
    else {
        PIDgyroY.SetMode(AUTOMATIC);
        PIDgyroY.SetOutputLimits(0, 45);
        PIDgyroY.SetSampleTime(10);
    }
    if(abs(anglez) <= 45) {
        PIDgyroZ.SetMode(AUTOMATIC);
        PIDgyroZ.SetOutputLimits(0, anglez);
        PIDgyroZ.SetSampleTime(10);
    }
    else {
        PIDgyroZ.SetMode(AUTOMATIC);
        PIDgyroZ.SetOutputLimits(0, 45);
        PIDgyroZ.SetSampleTime(10);
    }
}

void PID_Angle_Init() {
    
    PIDangleX.SetMode(AUTOMATIC);
    PIDangleX.SetOutputLimits(0, 90);
    PIDangleX.SetSampleTime(10);

    PIDangleY.SetMode(AUTOMATIC);
    PIDangleY.SetOutputLimits(0, 90);
    PIDangleY.SetSampleTime(10);

    PIDangleZ.SetMode(AUTOMATIC);
    PIDangleZ.SetOutputLimits(0, 90);
    PIDangleZ.SetSampleTime(10);
}

void Init_PID()
{
    PID_Angle_Init();
    PID_Gyro_Init();
}

void PID_Gyro_Compute() {
    PIDgyroX.SetTunings(kp, ki, kd); 
    PIDgyroX.Compute(); // measure the correction for the x angle The correction in this case can applied as an increase/decrease in the power level of the motors

    PIDgyroY.SetTunings(kp, ki, kd);
    PIDgyroY.Compute();

    PIDgyroZ.SetTunings(kp, ki, kd);
    PIDgyroZ.Compute();
}

void PID_Angle_Compute() {
    PIDangleX.SetTunings(kp, ki, kd); 
    PIDangleX.Compute(); // measure the correction for the x angle The correction in this case can applied as an increase/decrease in the power level of the motors

    PIDangleY.SetTunings(kp, ki, kd);
    PIDangleY.Compute();

    PIDangleZ.SetTunings(kp, ki, kd);
    PIDangleZ.Compute();
}

void Compute_PID()
{
    PID_Angle_Compute();
    PID_Gyro_Compute();

    if (abs(anglex) > 45 || abs(angley) > 45)
    {
        pid_output_x = 0; // motor stop when fall
        pid_output_y = 0;
    }
}

void PID_Tunning_Command() {
    switch (tunningCommandReceive.charRcv)
        case 'p':
            if(1) {
                kp += tunningCommandReceive.charRcv;
            }
            else {
                kp -= tunningCommandReceive.charRcv;
            }

}