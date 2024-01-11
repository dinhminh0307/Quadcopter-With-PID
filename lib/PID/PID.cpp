#include <PID.h>
#include <MPU.h>
#include <string.h>
// #include <ESPnow.h>
/*Note: if the motor and its axis does not work as how it must work, tunning the kp
================== PID explain =====================
---- kp: linear element that decides the speed of balancing Error to setpoint. kp increase -> the speed of balancing is fast
---- kd: the change of Error in dt, this constant used to adjust the speed from kp. If Error is large, the speed is large and vice versa. de = e - olde
---- ki: If kd is to large, so the de is 0 before it reach the setpoint, this constant used to increase the error until it reaches setpoint*/

double pid_output_x, pid_output_y, pid_output_z;
double anglex_setpoint, angley_setpoint, anglez_setpoint;
double kpX, kiX, kdX;
// pid for y axis
double kpY, kiY, kdY;
// pid for z axis
double kpZ, kiZ, kdZ;

double gyrox_setpoint, gyroy_setpoint, gyroz_setpoint;
/*to control the angle setpoint, it means that we need to control the angular velocity to stay at that setpoint
- Then that angular velocity will be gotten by controlling the speed of motor (cmd_send_motor)
Formula: angle -> v -> mo tor command*/
PID PIDgyroX(&anglex, &gyrox_setpoint, &anglex_setpoint, kpX, kiX, kdX, DIRECT);
PID PIDgyroY(&angley, &gyroy_setpoint, &angley_setpoint, kpY, kiY, kdY, DIRECT);
PID PIDgyroZ(&anglez, &gyroz_setpoint, &anglez_setpoint, kpZ, kiZ, kdZ, DIRECT);

PID PIDangleX(&gyrox, &pid_output_x, &gyrox_setpoint, kpX, kiX, kdX, DIRECT);
PID PIDangleY(&gyroy, &pid_output_y, &gyroy_setpoint, kpY, kiY, kdY, DIRECT);
PID PIDangleZ(&gyroz, &pid_output_z, &gyroz_setpoint, kpZ, kiZ, kdZ, DIRECT);

void PID_Gyro_Init()
{
    // if the current angle is below 45 => the desired angular vel is blew current angle, else
    PIDgyroX.SetMode(AUTOMATIC);
    PIDgyroX.SetOutputLimits(-90, 90);
    PIDgyroX.SetSampleTime(10);

    PIDgyroY.SetMode(AUTOMATIC);
    PIDgyroY.SetOutputLimits(-90, 90);
    PIDgyroY.SetSampleTime(10);

    PIDgyroZ.SetMode(AUTOMATIC);
    PIDgyroZ.SetOutputLimits(-90, 90);
    PIDgyroZ.SetSampleTime(10);
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
    // init input param
    anglex = 0;
    angley = 0;
    anglez = 0;
    // init setpoint
    anglex_setpoint = 0, angley_setpoint = 0, anglez_setpoint = 0;
    gyrox_setpoint = 0, gyroy_setpoint = 0, gyroz_setpoint = 0;
    kpY = 1.25;
    kdY = 0.006;
    kiY = 0.015;

    // tunning for pitch axis
    kpX = 0.90;
    kdX = 0.013;
    kiX = 0.015;

    // tunning for yaw axis
    kpZ = 0.75;
    kdZ = 0.00;
    kiZ = 0.00;
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
}

void displayPID()
{
    Serial.println("PID Tuning Values");
    Serial.println("================================");

    // Headers
    Serial.println("      | Pitch    | Roll     |Yaw     ");
    Serial.println("--------------------------------");

    // Row for Kp
    Serial.print("Kp    | ");
    Serial.print(kpY);
    Serial.print("   | ");
    Serial.print(kpX);
    Serial.print("   | ");
    Serial.println(kpZ);

    // Row for Kd
    Serial.print("Kd    | ");
    Serial.print(kdY);
    Serial.print("   | ");
    Serial.print(kdX);
    Serial.print("   | ");
    Serial.println(kdZ);

    // Row for Ki
    Serial.print("Ki    | ");
    Serial.print(kiY);
    Serial.print("   | ");
    Serial.print(kiX);
    Serial.print("   | ");
    Serial.println(kiZ);

    Serial.println("================================");
}
