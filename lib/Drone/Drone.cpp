#include "./Drone.h"
// Mac address of initator:  0x48,0xE7,0x29,0x96,0xBB,0x18
// Mac address of reciever: 48:E7:29:93:D8:24
// varible definitions
Servo ESC;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int val;
int escPWM = 18;
int escPWM2 = 19;
// int escPWM3 = 33;
int escPWM4 = 25;
voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;

uint8_t broadcastAddress[] = {0x48,0xE7,0x29,0x96,0xBB,0x18};   // mac address of remote

void onDataReceived(const uint8_t * mac, const uint8_t *incomingData, int len) {
      if(len == sizeof(recieved_Voltage)) {
        memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
        Serial.println(recieved_Voltage.voltageVal);
      }
        
    if(len == sizeof(received_Button)) {
        memcpy(&received_Button, incomingData, sizeof(received_Button));
        Serial.println(recieved_Voltage.voltageVal);
    }
}
void esp_now_config() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    // Initilize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    // Register callback function
    esp_now_register_recv_cb(onDataReceived);
}

void ESC_init() {
    ESC.attach(escPWM, 1000, 2000);
    ESC2.attach(escPWM2, 1000, 2000);
    // ESC3.attach(escPWM3, 1000, 2000);
    ESC4.attach(escPWM4, 1000, 2000);
}

void rotateBLDC() {
  int loopCount = 1;
  int myVal = recieved_Voltage.voltageVal;
  // check if the button is recieved yet
  if(received_Button.buttontState == INTERUPT_STATE) {
    myVal = 0;
  }
  while (true)
    {
      if (loopCount == 1)
      {
        ESC.write(myVal);
      }
      else if (loopCount == 2)
      {
        ESC2.write( myVal);
      }
      // else if (loopCount == 3)
      // {
      //   ESC3.write(recieved_Voltage.voltageVal);
      // }
      else if (loopCount == 4)
      {
        ESC4.write( myVal);
      }
      loopCount++;
      if (loopCount == 5)
      {
        break;
      }
      delay(100);
    }
}

void droneConfig() {
    ESC_init();
    esp_now_config();
}