#include <PID.h>
#include <MPU.h>
#include <string.h>

double pid_output_x, pid_output_y, pid_output_z;
double anglex_setpoint, angley_setpoint, anglez_setpoint;
double kpX = 0.5, kiX = 0.5, kdX = 0.5; 
// pid for y axis
double kpY = 1, kiY = 0, kdY = 0;
// pid for z axis
double kpZ = 0.5, kiZ = 0.5, kdZ = 0.5;

double gyrox_setpoint, gyroy_setpoint, gyroz_setpoint;
/*to control the angle setpoint, it means that we need to control the angular velocity to stay at that setpoint
- Then that angular velocity will be gotten by controlling the speed of motor (cmd_send_motor)
Formula: angle -> v -> motor command*/
PID PIDgyroX(&anglex, &gyrox_setpoint, &anglex_setpoint, kpX, kiX, kdX, DIRECT);
PID PIDgyroY(&angley, &gyroy_setpoint, &angley_setpoint, kpY, kiY, kdY, DIRECT);
PID PIDgyroZ(&anglez, &gyroz_setpoint, &anglez_setpoint, kpZ, kiZ, kdZ, DIRECT);

PID PIDangleX(&gyrox, &pid_output_x, &gyrox_setpoint, kpX, kiX, kdX, DIRECT);
PID PIDangleY(&gyroy, &pid_output_y, &gyroy_setpoint, kpY, kiY, kdY, DIRECT);
PID PIDangleZ(&gyroz, &pid_output_z, &gyroz_setpoint, kpZ, kiZ, kdZ, DIRECT);

void PID_Gyro_Init()
{
    // if the current angle is below 45 => the desired angular vel is blew current angle, else
    if (abs(anglex) <= 45)
    {
        PIDgyroX.SetMode(AUTOMATIC);
        PIDgyroX.SetOutputLimits(0, anglex);
        PIDgyroX.SetSampleTime(10);
    }
    else
    {
        PIDgyroX.SetMode(AUTOMATIC);
        PIDgyroX.SetOutputLimits(0, 45);
        PIDgyroX.SetSampleTime(10);
    }

    if (abs(angley) <= 45)
    {
        PIDgyroY.SetMode(AUTOMATIC);
        PIDgyroY.SetOutputLimits(0, angley);
        PIDgyroY.SetSampleTime(10);
    }
    else
    {
        PIDgyroY.SetMode(AUTOMATIC);
        PIDgyroY.SetOutputLimits(0, 45);
        PIDgyroY.SetSampleTime(10);
    }
    if (abs(anglez) <= 45)
    {
        PIDgyroZ.SetMode(AUTOMATIC);
        PIDgyroZ.SetOutputLimits(0, 0);
        PIDgyroZ.SetSampleTime(10);
    }
    else
    {
        PIDgyroZ.SetMode(AUTOMATIC);
        PIDgyroZ.SetOutputLimits(0, 0);
        PIDgyroZ.SetSampleTime(10);
    }
}

void PID_Angle_Init()
{

    PIDangleX.SetMode(AUTOMATIC);
    PIDangleX.SetOutputLimits(-90, 90); // extend the value range for motor command so that when the drone both pitch and roll for different direction, the command is still counted different to 0
    PIDangleX.SetSampleTime(10);

    PIDangleY.SetMode(AUTOMATIC);
    PIDangleY.SetOutputLimits(-90, 90);
    PIDangleY.SetSampleTime(10);

    PIDangleZ.SetMode(AUTOMATIC);
    PIDangleZ.SetOutputLimits(-90, 90);
    PIDangleZ.SetSampleTime(10);
}

void Init_PID()
{
    //init input param
    anglex = 0;
    angley = 0;
    anglez = 0;
    // init setpoint
    anglex_setpoint = 0, angley_setpoint = 0, anglez_setpoint = 0;
    gyrox_setpoint = 0, gyroy_setpoint = 0, gyroz_setpoint = 0;
    // init output
    pid_output_x = 0, pid_output_y = 0, pid_output_z = 0;
    // turn on PID
    PID_Angle_Init();
    PID_Gyro_Init();

}

void PID_Gyro_Compute()
{
    PIDgyroX.SetTunings(kpX, kiX, kdX);
    PIDgyroX.Compute(); // measure the correction for the x angle The correction in this case can applied as an increase/decrease in the power level of the motors

    PIDgyroY.SetTunings(kpY, kiY, kdY);
    PIDgyroY.Compute();

    PIDgyroZ.SetTunings(kpZ, kiZ, kdZ);
    PIDgyroZ.Compute();
}

void PID_Angle_Compute()
{
    PIDangleX.SetTunings(kpX, kiX, kdX);
    PIDangleX.Compute(); // measure the correction for the x angle The correction in this case can applied as an increase/decrease in the power level of the motors

    PIDangleY.SetTunings(kpY, kiY, kdY);
    PIDangleY.Compute();

    PIDangleZ.SetTunings(kpZ, kiZ, kdZ);
    PIDangleZ.Compute();
}

void Compute_PID()
{
    PID_Angle_Compute();
    PID_Gyro_Compute();

    /*Temporary remove this one*/
    // if (abs(anglex) > 45 || abs(angley) > 45)
    // {
    //     pid_output_x = 0; // motor stop when fall
    //     pid_output_y = 0;
    // }
}

