#include "./PID.h"

// pid var
double kp = 5.0, ki = 0.0, kd = 0.0;

// setpoint and output for pid
double pidPitchOutput, pidRollOutput, setpoint;
double pidPitchInput, pidRollInput;

PID pitchPID(&pidPitchInput, &pidPitchOutput, &setpoint, kp, ki, kd, DIRECT); // pid t controll pitch
PID rollPID(&pidRollInput, &pidRollOutput, &setpoint, kp, ki, kd, DIRECT);    // pid controll roll

void pitch_pid_init()
{
    pidPitchInput = getGyroReadings().GyroY;
    pitchPID.SetMode(AUTOMATIC);
    pitchPID.SetOutputLimits(0, 180);
    pitchPID.SetSampleTime(500);
}

void roll_pid_init()
{
    pidRollInput = getGyroReadings().GyroX;
    rollPID.SetMode(AUTOMATIC);
    rollPID.SetOutputLimits(0, 180);
    rollPID.SetSampleTime(500);
}

void yaw_pid_init()
{
    pidPitchInput = getGyroReadings().GyroY;
    pitchPID.SetMode(AUTOMATIC);
    pitchPID.SetOutputLimits(0, 180);
    pitchPID.SetSampleTime(1);
}
void PID_Init()
{

    initMPU();
    setpoint = 0;
    pitch_pid_init();
    roll_pid_init();
}

void PID_pitch()
{
    pidPitchInput = getGyroReadings().GyroY;
    pitchPID.Compute();
}

void PID_roll()
{
    pidRollInput = getGyroReadings().GyroX;
    rollPID.Compute();
}

void printPIDOutputValues()
{
    Serial.print("pitch: ");
    Serial.print(pidPitchOutput);
    Serial.print(" roll: ");
    Serial.println(pidRollOutput);
}