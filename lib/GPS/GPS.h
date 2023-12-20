#include <Arduino.h>
#include <TinyGPSPlus.h>
#include "./WifiInit.h"
#include <HTTPClient.h>
// ================================================================
// Variable declaration
// ================================================================
#define RXD2 16
#define TXD2 17
// The default baudrate of NEO-8M is 9600
#define GPS_BAUDRATE 9600

void initGPS(); //Initialize the GPS
void GetGPSData(); // Get the GPS data
void write_to_google_sheet(String params); //Write to google sheet