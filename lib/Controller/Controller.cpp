#if 0
#include "./Controller.h"

// Variables definitions
int potPin = 34;
button_t button_1;
button_message myButton;
voltage_stuct myPot;



uint8_t broadcastAddress[] = {0x48,0xE7,0x29,0x93,0xD8,0x24}; // mac address of receiver
void IRAM_ATTR button_isr()
{
  button_update(&button_1);
}

void buttonInit() {
  button_add_default(&button_1, BUTTON_1_PIN);
  button_init(&button_isr);
  Serial.begin(115200);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { // this is called when data is transmitted
  //Serial.println(">>>>>>>>>>>>>>>");
//   if(status == ESP_NOW_SEND_SUCCESS) {
//     Serial.println("Transfer complete");
//   }
//   else {
//     Serial.println("Fail to transmit");
//   }
}

void esp_now_config() {
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station.
  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(onDataSent); // call back function to getthe sent status into the  ondatasent
  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfo = {};
  //memset(&peerInfo, 0, sizeof(peerInfo)); // set peer, it could affect wifi
  memcpy(peerInfo.peer_addr, broadcastAddress, sizeof(broadcastAddress));
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //----------------------------------------

  //----------------------------------------Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  else {
    Serial.println("succssefull to add peer");
    return;
  }
}



int ADC_Read() {
  return map(analogRead(potPin), 0, 4095, 0, 180);
}

void potentiometerSend(int val) {
  myPot.voltageVal = val;
  esp_err_t dataSent = esp_now_send(broadcastAddress, (uint8_t *) &myPot, sizeof(myPot));
  // if(dataSent == ESP_OK) {
  //   Serial.println("Deliver success");
  // }
  Serial.println(myPot.voltageVal);
}

void buttonDataSend(int val) {
  myButton.button_status = val;
  esp_err_t dataSent = esp_now_send(broadcastAddress, (uint8_t *) &myButton, sizeof(myPot));
  if(dataSent == ESP_OK) {
    Serial.println("Deliver success");
  }
  Serial.println(myButton.button_status);
}

void buttonPressed(int val) {
  if(button_1.mode == 0) {
    potentiometerSend(val);
    button_1.mode = NONE;
  }
  else {
    buttonDataSend(INTERUPT_VAL);
    button_1.mode = NONE;
  }
}

void remoteControllerConfig() {
  buttonInit();
  esp_now_config();
}
#endif