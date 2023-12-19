#include "./PID.h"

// PID constants
double kp = 5.0, ki = 0.0, kd = 0.0;

// Setpoint and output for PID
double  pidPitchOutput, pidRollOutput, pidYawOutput, setpoint;
double pidPitchInput, pidRollInput, pidYawInput;
const int SAMPLE_TIME_INTERVAL = 1000;

// PID controllers
PID pitchPID(&pidPitchInput, &pidPitchOutput, &setpoint, kp, ki, kd, DIRECT);
PID rollPID(&pidRollInput, &pidRollOutput, &setpoint, kp, ki, kd, DIRECT);
PID yawPID(&pidYawInput, &pidYawOutput, &setpoint, kp, ki, kd, DIRECT); // Yaw PID

void PID_Init() {
    initMPU(); // Initialize MPU (gyro, accelerometer)
    setpoint = 0; // Setpoint for level flight and stationary yaw

    // Initialize Pitch PID
    pidPitchInput = getGyroReadings().GyroY; 
    pitchPID.SetMode(AUTOMATIC);
    pitchPID.SetOutputLimits(0, 180);
    pitchPID.SetSampleTime(SAMPLE_TIME_INTERVAL);

    // Initialize Roll PID
    pidRollInput = getGyroReadings().GyroX;
    rollPID.SetMode(AUTOMATIC);
    rollPID.SetOutputLimits(0, 180);
    rollPID.SetSampleTime(SAMPLE_TIME_INTERVAL);

    // Initialize Yaw PID
    pidYawInput = getGyroReadings().GyroZ; // Assuming GyroZ is yaw
    yawPID.SetMode(AUTOMATIC);
    yawPID.SetOutputLimits(0, 180); 
    yawPID.SetSampleTime(SAMPLE_TIME_INTERVAL);
}

// Update PID controllers
void updatePID() {
    pidPitchInput = getGyroReadings().GyroY;
    pidRollInput = getGyroReadings().GyroX;
    pidYawInput = getGyroReadings().GyroZ; // Update yaw input

    pitchPID.Compute();
    rollPID.Compute();
    yawPID.Compute(); // Compute yaw PID
}

// Print PID output values for debugging
void printPIDOutputValues() {
    Serial.print("Pitch: ");
    Serial.print(pidPitchOutput);
    Serial.print(", Roll: ");
    Serial.print(pidRollOutput);
    Serial.print(", Yaw: ");
    Serial.println(pidYawOutput); // Print yaw output
}