#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

extern double anglex, angley, anglez; // angle in the x, y, z direction
extern double gyrox, gyroy, gyroz;    // angle rate in the x, y, z direction
extern double accx, accy, accz;       // acceleration in the x, y, z direction

// ================================================================
// Function Declaration
// ================================================================
void Init_MPU();      // Function to init the MPU6050
void Get_MPUangle();  // Function to get the angle from the MPU6050
void Get_accelgyro(); // Function to get the gyro and acc from the MPU6050
