#include "./MPU.h"
#include <math.h>
#include "./Drone.h"
#include "./PID_LIB.h"

// pid var
double kp,ki,kd;

// setpoint and output for pid
double pid_output, setpoint = 0;
double pwmSend; // the pwm signal sent by pid to the esc

double mpu_sensor_roll; // get sensor of roll to pid
double mpu_sensor; // the pid input from the sensor of pitch

PID pitchPID(&mpu_sensor, &pid_output, &setpoint,kp,ki,kd, DIRECT); // pid t controll pitch
PID rollPID(&mpu_sensor_roll, &pid_output, &setpoint,kp,ki,kd, DIRECT); // pid controll roll
void PID_Init();
void PID_Send_Pitch();
void pitch_pid_init(); 
void roll_pid_init();

