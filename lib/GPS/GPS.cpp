#include "./GPS.h"
TinyGPSPlus gps;

void initGPS() {
    // Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);
    Get_GPSData();
}
void Get_GPSData() {
    // Get the GPS data
    while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
        //displayInfo();
}
