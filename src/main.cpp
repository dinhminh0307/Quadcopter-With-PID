#include <Arduino.h>
#include <WiFi.h>
#include "../lib/wireless/wireless.h"

void setup()
{
  Serial.begin(9600);
  espnow_initialize();
  Serial.println("Welcome to the Drone");
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void loop()
{
  // All processing is done in the OnDataReceive callback
}