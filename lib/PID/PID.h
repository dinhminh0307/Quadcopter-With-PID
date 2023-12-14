#include "./MPU.h"
#include <math.h>
#include "./Drone.h"
#include "./PID_LIB.h"

// pid var
double kp,ki,kd;

double pid_output, setpoint = 0;
double mpu_sensor; // the pid input from the sensor
double pwmSend; // the pwm signal sent by pid to the esc
PID pitchPID(&mpu_sensor, &pid_output, &setpoint,kp,ki,kd, DIRECT); // pid t controll pitch

void PID_Init();
void PID_Send_Pitch();
void pitch_pid_init(); 

