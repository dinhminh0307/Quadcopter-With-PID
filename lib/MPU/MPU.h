#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <math.h>
#define RAD_2_DEG 180/PI
void initMPU();
typedef struct {
    float accX;
    float accY;
    float accZ;
}data_recieved_acc;

typedef struct {
    float GyroX;
    float GyroY;
    float GyroZ;
}data_recieved_gyro;

data_recieved_gyro gyroDataSent;

float getGyroReadings();
void getAccReadings();
String getTemperature();
