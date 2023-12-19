#include <Arduino.h>
#include <TinyGPSPlus.h>
// ================================================================
// Variable declaration
// ================================================================
#define RXD2 16
#define TXD2 17
// The default baudrate of NEO-8M is 9600
#define GPS_BAUDRATE 9600

void initGPS(); //Initialize the GPS
void Get_GPSData(); // Get the GPS data
