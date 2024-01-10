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
  imuCalStatus.status = 300;
  if (imuCalStatus.status == 300)
  {

    esp_now_send(broadcastAddress, (uint8_t *)&imuCalStatus, sizeof(imuCalStatus));
    
  }

  // Init_GoogleSheet();
}

void loop()
{
  Get_MPUangle();
  Get_accelgyro();

  setBaseSpeed(); // called befor moving the drone and pid
  Compute_PID();
  displayPID(); // justused for printing

  // if(joystickSignalReceiver.x != 0) {
  //   applyPitch();
  // }
  // else {
  droneHovering();
  //}

  delay(500);
}
