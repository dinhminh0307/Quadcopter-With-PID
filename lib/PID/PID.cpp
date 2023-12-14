#include "./PID.h"

void pitch_pid_init() {
    getGyroReadings();
    mpu_sensor = gyroDataSent.GyroY;
    pitchPID.SetMode(AUTOMATIC);
}
void PID_Init() {
    ESC_init();
    initMPU();
}

void PID_Send_Pitch() {
    getGyroReadings();
    mpu_sensor = gyroDataSent.GyroY;
    pitchPID.SetTunings(kp,ki,kd);
    pitchPID.Compute();
    pwmSend = mpu_sensor;
}