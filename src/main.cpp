#include <Arduino.h>
/*Just a test so please ignore it, otherwise please test in the test folder
 */

#include <PID.h>
void setup()
{

  Serial.begin(115200);
  PID_Init();

  // droneConfig();
  // eventHandler();

  //  Serial.println("setup");
}

void loop()
{
  PID_pitch();
  PID_roll();
  printPIDOutputValues();
  // sendEvent();
  // rotateBLDC();
}