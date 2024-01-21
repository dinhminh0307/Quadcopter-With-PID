#include <Drone.h>
#include <ESPnow.h>
// Mac address of initator:  0x48,0xE7,0x29,0x96,0xBB,0x18
// Mac address of reciever: 48:E7:29:93:D8:24
// varible definitions
Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

// motor speed variable declaration
int motorSpeed1, motorSpeed2, motorSpeed3, motorSpeed4;
int baseSpeed;

double motor_cmd;
imu_struct_send imuInfoSender;
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
  delay(2000);
}

void rotateBLDC() {  
  // Stop the motors if the stop condition is met
  if (isStop == STOP) {
    motorSpeed1 = 0;
    motorSpeed2 = 0;
    motorSpeed3 = 0;
    motorSpeed4 = 0;
  }

  // Send back information (functionality of sendBackInfo is assumed)
  sendBackInfo();

  // Send IMU information using ESP-NOW
  esp_err_t dataSent = esp_now_send(broadcastAddress, (uint8_t *)&imuInfoSender, sizeof(imuInfoSender));

  // Send the speed command to each ESC (Electronic Speed Controller)
  for (int i = 1; i <= 4; ++i) {
    switch (i) {
      case 1:
        ESC.write(motorSpeed1);
        break;
      case 2:
        ESC2.write(motorSpeed2);
        break;
      case 3:
        ESC3.write(motorSpeed3);
        break;
      case 4:
        ESC4.write(motorSpeed4);
        break;
    }
    delay(10); // Delay after each command to allow the ESC to process it
  }
}

void setBaseSpeed()
{
  // Base speed from potentiometer
  baseSpeed = map(recieved_Voltage.voltageVal, 0, 180, 0, 90);
}


void droneHovering()
{
  // Calculate motor speeds based on PID outputs
  // This is a simplified example. You'll need to adjust the formula based on your quadcopter's design
  motorSpeed1 = baseSpeed + pid_output_x + pid_output_y + pid_output_z; // Motor 32
  motorSpeed2 = baseSpeed - pid_output_x + pid_output_y - pid_output_z; // Motor 25
  motorSpeed3 = baseSpeed - pid_output_x - pid_output_y + pid_output_z; // Motor 26
  motorSpeed4 = baseSpeed + pid_output_x - pid_output_y - pid_output_z; // Motor 33

  // Constrain motor speeds to be within 0 to 180
  motorSpeed1 = constrain(motorSpeed1, 0, 110);
  motorSpeed2 = constrain(motorSpeed2, 0, 110);
  motorSpeed3 = constrain(motorSpeed3, 0, 110);
  motorSpeed4 = constrain(motorSpeed4, 0, 110);

  rotateBLDC();
}

void sendBackInfo()
{
  imuInfoSender.anglex = anglex;
  imuInfoSender.angley = angley;
  imuInfoSender.anglez = anglez;
  imuInfoSender.gyrox = gyrox;
  imuInfoSender.gyroy = gyroy;
  imuInfoSender.gyroz = gyroz;
  imuInfoSender.motor1Speed = motorSpeed1;
  imuInfoSender.motor2Speed = motorSpeed2;
  imuInfoSender.motor3Speed = motorSpeed3;
  imuInfoSender.motor4Speed = motorSpeed4;

  esp_now_send(broadcastAddress, (uint8_t *)&imuInfoSender, sizeof(imuInfoSender));
}


