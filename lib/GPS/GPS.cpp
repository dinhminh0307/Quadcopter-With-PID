#include "./GPS.h"
TinyGPSPlus gps;
HardwareSerial neogps(1);

//Enter the google sheet script id
String GOOGLE_SCRIPT_ID = "AKfycbzcwI1hU_NA7lkmDErIEX7fifLU3WsGtHhMLQfOTaeR7g4SQuawbIQnUKLcxM0n5NoTRQ";

//Time delay in ms
const int sendInterval = 2000; //Delay 2s

void initGPS() {
    // Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);
    delay(10);
    //Wifi
    // iniWiFi();
}

void GetGPSData() {
    // Get the GPS data
    while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
    {
        String param = "";
        //Check latitude and longtitude
        if(gps.location.isValid())
        {
            param  = "latitude=" + String(gps.location.lat(), 6);
            param += "&longitude=" + String(gps.location.lng(), 6);
        }
        else
        {
            param  = "latitude=INVALID";
            param += "&longitude=INVALID";
        }

        //Check speed
        if(gps.speed.isValid())
            param += "&speed=" + String(gps.speed.kmph());
        else
            param += "&speed=INVALID";

        //Check # of satellites
        if(gps.satellites.isValid())
            param += "&satellites=" + String(gps.satellites.value());
        else
            param += "&satellites=INVALID";

        //Check altitude
        if(gps.altitude.isValid())
            param += "&altitude=" + String(gps.altitude.meters());
        else
            param += "&altitude=INVALID";

        //Check time
        if(gps.time.isValid())
        {
            //Hour
            if (gps.time.hour() < 10)
                param += "&gps_time=0" + String(gps.time.hour());
            else
                param += "&gps_time=" + String(gps.time.hour());

            param += ":";

            //Minute
            if (gps.time.minute() < 10)
                param += "0" + String(gps.time.minute());
            else
                param += String(gps.time.minute());

            param += ":";

            //Second
            if (gps.time.second() < 10)
                param += "0" + String(gps.time.second());
            else
                param += String(gps.time.second());  
        }
        else
            param += "&gps_time=INVALID";

        //Check date
        if(gps.date.isValid())
            param += "&gps_date=" + String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
        else
            param += "&gps_date=INVALID";
        
        //Print data to Serial
        Serial.println(param);
        //Print data in google sheet through wifi
        //write_to_google_sheet(param);

    }
}

void write_to_google_sheet(String params) {
   HTTPClient http;
   String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + params;
   //Serial.print(url);
    Serial.println("Postring GPS data to Google Sheet");
    //---------------------------------------------------------------------
    //starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: "+payload);     
    }
    //---------------------------------------------------------------------
    http.end();
}