
#include <Arduino.h>
#include <ESP32Servo.h>
#include "./motor.h"

Servo ESC1; // Define the ESC

void Init_ESC()
{
    ESC1.attach(MOTOR_PIN_1, MIN_SIGNAL, MAX_SIGNAL);
    ESC1.writeMicroseconds(MIN_SIGNAL);
}

void runningMotor1(int CtrlPWM)
{
    ESC1.write(CtrlPWM); // Send the command to the ESC
}