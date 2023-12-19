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

// data object
extern data_recieved_gyro gyroDataSent;
extern data_recieved_acc accDataSent;


data_recieved_gyro getGyroReadings();
data_recieved_acc getAccReadings();
String getTemperature();
