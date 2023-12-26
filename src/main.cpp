#include <Arduino.h>
#include <Serial.h>
#include <MPU.h>
#include <Drone.h>
#include <ESPnow.h>
#include <GPS.h>
// #include <GoogleSheet.h>
#include <PID.h>

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
  Compute_PID();
  rotateBLDC();
  // recordGPStoGoogleSheet();
  SerialDataPIDPrint();
  // Serial.println("in loop");
}
