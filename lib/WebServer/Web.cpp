#include "./Web.h"

// Replace with your network credentials
const char *ssid = "DongLao";
const char *password = "Ntn.1991";

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
// Adafruit_MPU6050 mpu;

//sensors_event_t a, g, temp;

float gyroX, gyroY, gyroZ;
float AccX, AccY, AccZ;
// float temperature;

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

void webServerHandler() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    gyroX=0;
    gyroY=0;
    gyroZ=0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetX", HTTP_GET, [](AsyncWebServerRequest *request){
    gyroX=0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetY", HTTP_GET, [](AsyncWebServerRequest *request){
    gyroY=0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetZ", HTTP_GET, [](AsyncWebServerRequest *request){
    gyroZ=0;
    request->send(200, "text/plain", "OK");
  });
}

void eventHandler() {
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  server.begin();
}

void sendEvent() {
  if ((millis() - lastTime) > gyroDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getGyroWeb().c_str(),"gyro_readings",millis());
    lastTime = millis();
  }
  if ((millis() - lastTimeAcc) > accelerometerDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getAccWeb().c_str(),"accelerometer_readings",millis());
    lastTimeAcc = millis();
  }
  if ((millis() - lastTimeTemperature) > temperatureDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getTemperature().c_str(),"temperature_reading",millis());
    lastTimeTemperature = millis();
  }
}