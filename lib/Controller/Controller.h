#ifndef Controller_H
#define Controller_H
#include <ESP32Servo.h>
#include <esp32_button.h>
#define BUTTON_1_PIN 33

Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

bool flag = false;
int btnPin = 33;
int potPin = 4;
int val;
int escPWM = 18;
int escPWM2 = 19;
// int escPWM3 = 33;
int escPWM4 = 25;

button_t button_1;

void buttonInit();
void rotateBLDC(int myVal);
#endif