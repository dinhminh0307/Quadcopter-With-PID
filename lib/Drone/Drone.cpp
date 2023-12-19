#include "./Drone.h"
// Mac address of initator:  0x48,0xE7,0x29,0x96,0xBB,0x18
// Mac address of reciever: 48:E7:29:93:D8:24
// varible definitions
Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int val;
int escPWM = 32;
int escPWM2 = 26;
int escPWM3 = 33;
int escPWM4 = 25;
// daata struct
voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;
cal_signal_receive calSignalReceiver;

uint8_t broadcastAddress[] = {0x48, 0xE7, 0x29, 0x96, 0xBB, 0x18}; // mac address of remote

void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len)
{

  // Serial.println("receive data");

  if (len == sizeof(recieved_Voltage))
  { // receive the pot command from the sender
    memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
    Serial.println(recieved_Voltage.voltageVal);
  }

  // if (len == sizeof(received_Button))
  // { // receive button data
  //   memcpy(&received_Button, incomingData, sizeof(received_Button));
  //   Serial.println(recieved_Voltage.voltageVal);
  // }
  if (len == sizeof(calSignalReceiver))
  {
    memcpy(&calSignalReceiver, incomingData, sizeof(calSignalReceiver));
  }
}
void esp_now_config()
{

  WiFi.mode(WIFI_STA);
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register callback function
  esp_now_register_recv_cb(onDataReceived);
}
unsigned long previousMillis = 0;
const long interval = 3000;
void ESC_init()
{

  ESC.attach(escPWM, 1000, 2000);   // 32pin
  ESC2.attach(escPWM2, 1000, 2000); //// 26
  ESC3.attach(escPWM3, 1000, 2000); //// 33
  ESC4.attach(escPWM4, 1000, 2000); //// 25

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
  int loopCount = 1;
  // send the command to ESC
  while (true)
  {
    switch (loopCount)
    {
    case 1:
        ESC.write(recieved_Voltage.voltageVal);
        break;
    case 2:
        ESC2.write(recieved_Voltage.voltageVal);
        break;
    case 3:
        ESC3.write(recieved_Voltage.voltageVal);
        break;
    case 4:
        ESC4.write(recieved_Voltage.voltageVal);
        break;
    }

    delay(500); // Delay after each command

    loopCount++;
    if (loopCount > 4)
    {
        loopCount = 1;
    }
  }
}

void droneConfig()
{
  esp_now_config();
  ESC_init();
}