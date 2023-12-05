#include "./Drone.h"
void onDataReceived(const uint8_t * mac, const uint8_t *incomingData, int len) {
    if(len == sizeof(recieved_Voltage)) {
        memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
    }
    if(len == sizeof(received_Button)) {
        memcpy(&received_Button, incomingData, sizeof(received_Button));
    }
}
void esp_now_config() {
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
    myVal = received_Button.buttontState;
  }
  while (true)
    {
      if (loopCount == 1)
      {
        ESC.write(recieved_Voltage.voltageVal);
      }
      else if (loopCount == 2)
      {
        ESC2.write(recieved_Voltage.voltageVal);
      }
      // else if (loopCount == 3)
      // {
      //   ESC3.write(recieved_Voltage.voltageVal);
      // }
      else if (loopCount == 4)
      {
        ESC4.write(recieved_Voltage.voltageVal);
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