/*Just a test so please ignore it, otherwise please test in the test folder*/
#include <ESP32Servo.h>

// Servo ESC;
// Servo ESC2;
Servo ESC3;
// Servo ESC4;
// btnPin = 33;
int potPin  = 4;
int val;

// int escPWM = 18;
// int escPWM2 = 19;
int escPWM3 = 33;
// int escPWM4 = 25;

void setup() {
  // ESC.attach(escPWM, 1000, 2000);
  // ESC2.attach(escPWM2, 1000, 2000);
  ESC3.attach(escPWM3, 1000, 2000);
  //ESC4.attach(escPWM4, 1000, 2000);
  //Serial.begin(9600);
}

void loop() {
  val = analogRead(potPin);
  val = map(val, 0, 4095, 0, 180);
  // Serial.println(val);
  // ESC.write(val);
  // ESC2.write(val);
  ESC3.write(val);
  // ESC4.write(val);
  //delay(100);
}

// /*Testing external interupt*/
// #if 0 // 
// Servo ESC;
// Servo ESC2;
// int btnPin = 33;
// int potPin  = 4;

// // Volatile var
// volatile int val;
// volatile boolean flag = false;
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   ESC.attach(13,1000,2000);
//   ESC2.attach(18,1000,2000);
//   pinMode(btnPin, INPUT_PULLUP);
//   attachInterrupt(btnPin, ISR, FALLING);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(flag) {
//     val = 50;
//     Serial.println(val);
//     flag = false;
//   }
//   else {
//     val = analogRead(potPin);
//     val = map(val, 0, 4095, 0, 180);
//     Serial.println(val);
//     ESC.write(val);
//     ESC2.write(val);
//   }
//   delay(100);
// }

// void IRAM_ATTR ISR() {
//   flag = true;
// }
// #endif
// #if 0

// /*Testing 2 way communication between ESP32*/
// //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Getting_the_Boards_MAC_Address
// //----------------------------------------Load libraries
// #include "WiFi.h"
// //----------------------------------------

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   WiFi.mode(WIFI_MODE_STA);
//   Serial.println(WiFi.macAddress());
// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID LOOP
// void loop() {
//   // put your main code here, to run repeatedly:

// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



// //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> One-way communication ESP32 Sender
// /*
//   Rui Santos
//   Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files.
  
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
// */

// //----------------------------------------Load libraries
// #include <esp_now.h>
// #include <WiFi.h>
// //----------------------------------------

// uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //--> REPLACE WITH THE MAC Address of your receiver / ESP32 Receiver.

// //----------------------------------------Variables to accommodate the data to be sent.
// int send_rnd_val_1;
// int send_rnd_val_2;
// //----------------------------------------

// String success; //--> Variable to store if sending data was successful.

// //----------------------------------------Structure example to send data
// // Must match the receiver structure
// typedef struct struct_message {
//     int rnd_1;
//     int rnd_2;
// } struct_message;

// struct_message send_Data; //--> Create a struct_message to send data.
// //----------------------------------------

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//   if (status ==0){
//     success = "Delivery Success :)";
//   }
//   else{
//     success = "Delivery Fail :(";
//   }
//   Serial.println(">>>>>");
// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
// void setup() {
//   Serial.begin(115200);
 
//   WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station.

//   //----------------------------------------Init ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
//   //----------------------------------------
  
//   //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
//   // get the status of Trasnmitted packet
//   esp_now_register_send_cb(OnDataSent);
//   //----------------------------------------
  
//   //----------------------------------------Register peer
//   esp_now_peer_info_t peerInfo;
//   memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
//   //----------------------------------------
  
//   //----------------------------------------Add peer        
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
//   //----------------------------------------
// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID LOOP
// void loop() {
//   //----------------------------------------Set values to send
//   send_rnd_val_1 = random(0, 255);
//   send_rnd_val_2 = random(0, 255);
//   send_Data.rnd_1 = send_rnd_val_1;
//   send_Data.rnd_2 = send_rnd_val_2;
//   //----------------------------------------
  
//   Serial.println();
//   Serial.print(">>>>> ");
//   Serial.println("Send data");

//   //----------------------------------------Send message via ESP-NOW
//   esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
   
//   if (result == ESP_OK) {
//     Serial.println("Sent with success");
//   }
//   else {
//     Serial.println("Error sending the data");
//   }
//   //----------------------------------------
  
//   delay(5000);
// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// #endif