#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPSPlus.h>
#include <GPS.h>
#include <MPU.h>

void Init_GoogleSheet();
void recordGPStoGoogleSheet();
void recordMPUGoogleSheet();
void writeGoogleSheet(String params);