#include "Arduino.h"
#include "WiFi.h"

void setup()
{
    Serial.begin(9600);
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("Hello There");
    Serial.println(WiFi.macAddress());
}

void loop()
{
    Serial.println(WiFi.macAddress());
    delay(1000);
}