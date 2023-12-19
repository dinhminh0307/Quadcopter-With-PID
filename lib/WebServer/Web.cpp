#include "./Web.h"

// Replace with your network credentials
const char *ssid = "5A1-8";
const char *password = "sky25a18";

// Data structure

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Timer variables
unsigned long lastTime = 0;
unsigned long lastTimeTemperature = 0;
unsigned long lastTimeAcc = 0;
unsigned long gyroDelay = 10;
unsigned long temperatureDelay = 1000;
unsigned long accelerometerDelay = 200;

// Create a sensor object
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

float gyroX, gyroY, gyroZ;
float AccX, AccY, AccZ;
float temperature;

// Gyroscope sensor deviation
float gyroXerror = 0.07;
float gyroYerror = 0.03;
float gyroZerror = 0.01;

// Init MPU6050


void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

String getGyroWeb()
{
  // mpu.getEvent(&a, &g, &temp);

  // float gyroX_temp = g.gyro.x;
  // if (abs(gyroX_temp) > gyroXerror)
  // {
  //   gyroX += gyroX_temp / 50.00;
  // }

  // float gyroY_temp = g.gyro.y;
  // if (abs(gyroY_temp) > gyroYerror)
  // {
  //   gyroY += gyroY_temp / 70.00;
  // }

  // float gyroZ_temp = g.gyro.z;
  // if (abs(gyroZ_temp) > gyroZerror)
  // {
  //   gyroZ += gyroZ_temp / 90.00;
  // }
  
  gyroX = getGyroReadings().GyroX;
  gyroY = getGyroReadings().GyroY;
  gyroZ = getGyroReadings().GyroZ;
  readings["gyroX"] = String(gyroX);
  readings["gyroY"] = String(gyroY);
  readings["gyroZ"] = String(gyroZ);

  String jsonString = JSON.stringify(readings);
  return jsonString;
}

String getAccWeb()
{
  
  // Get current acceleration values
  AccX = getAccReadings().accX;
  AccY = getAccReadings().accY;
  AccZ = getAccReadings().accZ;
  readings["accX"] = String(AccX);
  readings["accY"] = String(AccY);
  readings["accZ"] = String(AccZ);
  String accString = JSON.stringify(readings);
  return accString;
}

String getTemperature()
{
  // mpu.getEvent(&a, &g, &temp);
  // temperature = temp.temperature;
  // return String(temperature);
}