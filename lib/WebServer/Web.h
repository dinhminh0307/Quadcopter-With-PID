/*Testing MPU6050*/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
#include <Arduino_JSON.h>
#include "SPIFFS.h"
#include "../MPU/MPU.h"
#include "../GPS/GPS.h"

String getGyroWeb();
String getAccWeb();
String getTemperature();
void initSPIFFS();
void initWiFi();
void webServerHandler();
void eventHandler();
void sendEvent();
