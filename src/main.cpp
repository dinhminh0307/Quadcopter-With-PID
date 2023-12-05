/*Just a test so please ignore it, otherwise please test in the test folder
*/


#if 0
void setup() {
  Serial.begin(115200);
  initWiFi();
  initSPIFFS();
  initMPU();

  // Handle Web Server
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

  // Handle Web Server Events
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

void loop() {
  if ((millis() - lastTime) > gyroDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getGyroReadings().c_str(),"gyro_readings",millis());
    lastTime = millis();
  }
  if ((millis() - lastTimeAcc) > accelerometerDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getAccReadings().c_str(),"accelerometer_readings",millis());
    lastTimeAcc = millis();
  }
  if ((millis() - lastTimeTemperature) > temperatureDelay) {
    // Send Events to the Web Server with the Sensor Readings
    events.send(getTemperature().c_str(),"temperature_reading",millis());
    lastTimeTemperature = millis();
  }
}

#endif

/*Testing external interupt*/
#if 0 //
#include <esp32_button.h>

#define BUTTON_1_PIN 33


button_t button_1;

void IRAM_ATTR button_isr()
{
  button_update(&button_1);
}

void setup()
{
  Serial.begin(9600);

  button_add_default(&button_1, BUTTON_1_PIN);

  button_init(&button_isr);
}

void loop()
{
  if (button_1.mode)
  {
    // Print modes: 1- Clicked, 2- Double Clicked 3- Long Pressed
    Serial.println(button_1.mode);

    // Reset modes
    button_1.mode = NONE;
  }
  else {
    Serial.println(button_1.mode);
  }

  delay(1000);
}
#endif




