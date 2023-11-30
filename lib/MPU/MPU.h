#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

void initMPU();
typedef struct {
    float accX;
    float accY;
    float accZ;
}data_recieved_acc;

void getGyroReadings();
void getAccReadings();
String getTemperature();
