#include <Arduino.h>
#include <WiFi.h>
#include ".."

void setup()
{
    Serial.begin(9600);
    WiFi.mode(WIFI_MODE_STA);
    espnow_initialize();
    Serial.println("Welcome to the Drone");
    Serial.println(WiFi.macAddress());
}

void loop()
{
    Serial.println(WiFi.macAddress());
    delay(1000);
}