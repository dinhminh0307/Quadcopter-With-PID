#include <Arduino.h>
#include <Serial.h>
#include <MPU.h>
#include <Drone.h>
#include <GPS.h>
#include <PID.h>
#include <ESPnow.h>

void setup()
{
  Init_Serial();
  // Init_Serial2(); // for the gps
  Init_ESPnow();
  Init_ESC();
  Init_MPU();
  Init_PID();

  // Init_GoogleSheet();
}

void loop()
{
  Get_MPUangle();
  Get_accelgyro();
  //   // Serial.print(anglex);
  //   // Serial.print(" ");
  //   // Serial.print(angley);
  //   // Serial.print(" ");
  //   // Serial.println(anglez);
  setBaseSpeed(); // called befor moving the drone and pid
  Compute_PID();
  // displayPID(); // justused for printing

  // if(joystickSignalReceiver.x != 0) {
  //   applyPitch();
  // }
  // else {
  droneHovering();
  //}
  delay(500);
}
