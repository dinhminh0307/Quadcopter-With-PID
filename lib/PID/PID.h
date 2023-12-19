#include <MPU.h>
#include <math.h>
#include <PID_LIB.h>


extern double pidPitchOutput, pidRollOutput, pidYawOutput, setpoint;

void PID_Init();
void updatePID();
void printPIDOutputValues();