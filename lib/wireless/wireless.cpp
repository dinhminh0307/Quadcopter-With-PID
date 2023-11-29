
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
struct_msg_Receive Receive_Data;
struct_msg_Sent Sent_Data;

// Variable for espnow communication
esp_now_peer_info_t peerInfo;

// Serial
unsigned long time_prev_serial = 0;

// ******************************************
// Function definition
// ******************************************
void SerialDataWrite()
{
    Serial.print(micros() / 1000);
    Serial.print("\t");
    Serial.print(Receive_Data.Receive_PotValue);
    Serial.print("\t");
    Serial.print(Sent_Data.Sent_PotAngle);
    Serial.println();
}

void OnDataReceive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // debugging serial
    Serial.print(micros() / 1000);
    Serial.println("\tData received!");
    // You must copy the incoming data to the local variables
    memcpy(&Receive_Data, incomingData, sizeof(Receive_Data));
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    // There is nothing to do when sending data, this is just for debugging
    Serial.print(micros() / 1000);
    Serial.println("\tData sent!");
    // Serial.print("\r\nLast Packet Send Status:\t");
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
    esp_now_register_send_cb(OnDataSent);

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