#include <GoogleSheet.h>
#include <ESPnow.h>
#include <esp_now.h>
// Replace with your network credentials
const char *ssid = "Donglao";
const char *password = "Ntn.1991";

TinyGPSPlus gps;

// Enter the google sheet script id
const String GPS_GOOGLE_SCRIPT_ID = "AKfycbzcwI1hU_NA7lkmDErIEX7fifLU3WsGtHhMLQfOTaeR7g4SQuawbIQnUKLcxM0n5NoTRQ";
const String IMU_GOOGLE_SCRIPT_ID = "AKfycbyRkC0qvVPZ-zysX_nEwLutK1uqZ5_9UvHCH3yp495s2h_NVAVYrJSI-Yf4BXLLnzNEng";
// imu_struct_send imuInfoSender;
String gpsParam;
String imuParam;
// Time delay in ms
// const int sendInterval = 2000; // Delay 2s
const int sendInterval = 0; // Delay 2s

// Initialize WiFi
void Init_GoogleSheet()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println(WiFi.localIP());
}

void recordGPStoGoogleSheet()
{
    // Get the GPS data
    while (Serial2.available() > 0)
        if (gps.encode(Serial2.read()))
        {
            gpsParam = "";
            // Check latitude and longtitude
            if (gps.location.isValid())
            {
                gpsParam = "latitude=" + String(gps.location.lat(), 6);
                gpsParam += "&longitude=" + String(gps.location.lng(), 6);
            }
            else
            {
                gpsParam = "latitude=INVALID";
                gpsParam += "&longitude=INVALID";
            }

            // Check speed
            if (gps.speed.isValid())
                gpsParam += "&speed=" + String(gps.speed.kmph());
            else
                gpsParam += "&speed=INVALID";

            // Check # of satellites
            if (gps.satellites.isValid())
                gpsParam += "&satellites=" + String(gps.satellites.value());
            else
                gpsParam += "&satellites=INVALID";

            // Check altitude
            if (gps.altitude.isValid())
                gpsParam += "&altitude=" + String(gps.altitude.meters());
            else
                gpsParam += "&altitude=INVALID";

            // Check time
            if (gps.time.isValid())
            {
                // Hour
                if (gps.time.hour() < 10)
                    gpsParam += "&gps_time=0" + String(gps.time.hour());
                else
                    gpsParam += "&gps_time=" + String(gps.time.hour());

                gpsParam += ":";

                // Minute
                if (gps.time.minute() < 10)
                    gpsParam += "0" + String(gps.time.minute());
                else
                    gpsParam += String(gps.time.minute());

                gpsParam += ":";

                // Second
                if (gps.time.second() < 10)
                    gpsParam += "0" + String(gps.time.second());
                else
                    gpsParam += String(gps.time.second());
            }
            else
                gpsParam += "&gps_time=INVALID";

            // Check date
            if (gps.date.isValid())
                gpsParam += "&gps_date=" + String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
            else
                gpsParam += "&gps_date=INVALID";

            // Print data to Serial
            // Serial.println(gpsParam);
            // Print data in google sheet through wifi
            // writeGoogleSheet(gpsParam, 0);
            break;
        }
}

void recordMPUtoGoogleSheet()
{
    imuParam = "";
    imuParam += "anglex=" + String(anglex);
    imuParam += "&angley=" + String(angley);
    imuParam += "&anglez=" + String(anglez);
    imuParam += "&gyrox=" + String(gyrox);
    imuParam += "&gyroy=" + String(gyroy);
    imuParam += "&gyroz=" + String(gyroz);

    Serial.println(imuParam);
    // imuInfoSender.anglex = anglex;
    // imuInfoSender.angley = angley;
    // imuInfoSender.anglez = anglez;
    // imuInfoSender.gyrox = gyrox;
    // imuInfoSender.gyroy = gyroy;
    // imuInfoSender.gyroz = gyroz;
    // esp_err_t dataSent = esp_now_send(broadcastAddress, (uint8_t *)&imuInfoSender, sizeof(imuInfoSender));
    // writeGoogleSheet(imuParam , 1);
}

void writeGoogleSheet(String params, int flag)
{
    String script = "";
    HTTPClient http;
    // 0 is GPS, 1 is MPU
    if (flag == 0)
        script = GPS_GOOGLE_SCRIPT_ID;
    else
        script = IMU_GOOGLE_SCRIPT_ID;

    // Create URL
    String url = "https://script.google.com/macros/s/" + script + "/exec?" + params;
    // Serial.print(url);
    Serial.println("Postring data to Google Sheet ");
    //---------------------------------------------------------------------
    // starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    // getting response from google sheet
    String payload;
    if (httpCode > 0)
    {
        payload = http.getString();
        Serial.println("Payload: " + payload);
    }
    //---------------------------------------------------------------------
    http.end();
}