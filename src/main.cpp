#include <Arduino.h>
#include <Serial.h>
#include <PID.h>
#include <Drone.h>


void setup()
{
  Init_Serial();
  PID_Init();
  droneConfig();
}

void loop()
{

  updatePID();
  printPIDOutputValues();
  rotateBLDC();
}

