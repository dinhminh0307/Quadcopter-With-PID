#include <Arduino.h>
#include <WiFi.h>
#include "../lib/wireless/wireless.h"

struct_msg_Receive receivedData;

// Forward declaration of the callback function
void OnDataReceive(const uint8_t *mac, const uint8_t *incomingData, int len);

void setup()
{
    Serial.begin(9600);
    espnow_initialize();
    Serial.println("Welcome to the Drone");
}

void loop()
{
    // All processing is done in the OnDataReceive callback
}