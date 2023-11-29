
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "wireless.h"

// ******************************************
// Variable declaration
// ******************************************
// Insert the MAC address of the remote
uint8_t broadcastAddress[] = {0xA8, 0x42, 0xE3, 0x47, 0x8A, 0x40};

// Declare the structure
struct_msg_Receive_Joystick Receive_Data_Joystick;
struct_msg_Receive_JTButton Receive_Data_JTButton;
struct_msg_Receive_POT Receive_Data_POT;

// Variable for espnow communication
esp_now_peer_info_t peerInfo;

// Serial
unsigned long time_prev_serial = 0;

// ******************************************
// Function definition
// ******************************************

void OnDataReceive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    if (len == sizeof(struct_msg_Receive_Joystick))
    {
        memcpy(&Receive_Data_Joystick, incomingData, sizeof(struct_msg_Receive_Joystick));

        Serial.print("Joystick X: ");
        Serial.print(Receive_Data_Joystick.joystickX);
        Serial.print(", Joystick Y: ");
        Serial.println(Receive_Data_Joystick.joystickY);
    }
    else if (len == sizeof(struct_msg_Receive_JTButton))
    {
        memcpy(&Receive_Data_JTButton, incomingData, sizeof(struct_msg_Receive_Joystick));
        if (Receive_Data_JTButton.pressed)
        {
            Serial.println("Joystick button was pressed!");
        };
    }
    else if (len == sizeof(struct_msg_Receive_POT))
    {
        memcpy(&Receive_Data_POT, incomingData, sizeof(struct_msg_Receive_POT));
        Serial.print("POT : ");
        Serial.println(Receive_Data_POT.value);
    }
}

void espnow_initialize()
{
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataReceive);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}