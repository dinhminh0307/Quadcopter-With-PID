#include <Drone.h>
#include <PID.h>
#include <ESPnow.h>
// Mac address of initator:  0x48,0xE7,0x29,0x96,0xBB,0x18
// Mac address of reciever: 48:E7:29:93:D8:24
// varible definitions
Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

double motor_cmd;

unsigned long previousMillis = 0;
const long interval = 3000;
void Init_ESC()
{

  ESC.attach(ESC_PWM, 1000, 2000);   // 32pin
  ESC2.attach(ESC_PWM2, 1000, 2000); //// 26
  ESC3.attach(ESC_PWM3, 1000, 2000); //// 33
  ESC4.attach(ESC_PWM4, 1000, 2000); //// 25

  // when disconnecting battery
  while (calSignalReceiver.signal != MAX_SIGNAL || calSignalReceiver.state != MAX_SIGNAL_STATE)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time the loop was run
      previousMillis = currentMillis;

      // your repetitive task here
      Serial.println("Waiting for max signal");
    }
  }

  // wait for data receive

  ESC.writeMicroseconds(MAX_SIGNAL);
  ESC2.writeMicroseconds(MAX_SIGNAL);
  ESC3.writeMicroseconds(MAX_SIGNAL);
  ESC4.writeMicroseconds(MAX_SIGNAL);
  Serial.print("set max value: ");
  Serial.println(calSignalReceiver.signal);

  while (calSignalReceiver.signal != MIN_SIGNAL || calSignalReceiver.state != MIN_SIGNAL_STATE)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time the loop was run
      previousMillis = currentMillis;

      // your repetitive task here
      Serial.println("Waiting for min signal");
    }

  } // wait for data received
  ESC.writeMicroseconds(MIN_SIGNAL);
  ESC2.writeMicroseconds(MIN_SIGNAL);
  ESC3.writeMicroseconds(MIN_SIGNAL);
  ESC4.writeMicroseconds(MIN_SIGNAL);
  Serial.print("set min value: ");
  Serial.println(calSignalReceiver.signal);
}

void rotateBLDC()
{

  // Base speed from potentiometer
  int baseSpeed = recieved_Voltage.voltageVal;

  // Calculate motor speeds based on PID outputs
  // This is a simplified example. You'll need to adjust the formula based on your quadcopter's design
  // int motorSpeed1 = baseSpeed + pidPitchOutput - pidRollOutput + pidYawOutput; // Motor 32
  // int motorSpeed2 = baseSpeed + pidPitchOutput + pidRollOutput - pidYawOutput; // Motor 26
  // int motorSpeed3 = baseSpeed - pidPitchOutput - pidRollOutput - pidYawOutput; // Motor 33
  // int motorSpeed4 = baseSpeed - pidPitchOutput + pidRollOutput + pidYawOutput; // Motor 25

  // Constrain motor speeds to be within 0 to 180
  // motorSpeed1 = constrain(motorSpeed1, 0, 180);
  // motorSpeed2 = constrain(motorSpeed2, 0, 180);
  // motorSpeed3 = constrain(motorSpeed3, 0, 180);
  // motorSpeed4 = constrain(motorSpeed4, 0, 180);

  int loopCount = 1;
  // send the command to ESC
  // while (true)
  // {
  //   switch (loopCount)
  //   {
  //   case 1:
  //     ESC.write(motorSpeed1);
  //     break;
  //   case 2:
  //     ESC2.write(motorSpeed2);
  //     break;
  //   case 3:
  //     ESC3.write(motorSpeed3);
  //     break;
  //   case 4:
  //     ESC4.write(motorSpeed4);
  //     break;
  //   }

    delay(500); // Delay after each command

    loopCount++;
    if (loopCount > 4)
    {
      loopCount = 1;
    }
  }

