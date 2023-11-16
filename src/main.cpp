#include <ESP32Servo.h>
Servo ESC;
int potPin  = 4;
int val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(val);
  ESC.write(val);
}

