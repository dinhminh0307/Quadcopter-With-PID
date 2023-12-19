#include <Arduino.h>
/*Just a test so please ignore it, otherwise please test in the test folder
 */

// #include <Drone.h>
#include <Web.h>
void setup()
{
  Serial.begin(115200);
  initMPU();
  initGPS();
  initSPIFFS();
  initWiFi();
  webServerHandler();
  eventHandler();
  //droneConfig();
  // Serial.println("setup");
}

void loop()
{
  sendEvent();
  //rotateBLDC();
}
// #if 0
// #include "./../lib/Drone/Drone.h"
// #include <MPU.h>
// #include <math.h>
// float kp=.5;
// float ki=55;
// float kd=.00001;

// Servo rollServo;
// int milliOld;
// int milliNew;
// int dt;

// float rollTarget=0;
// float rollActual;
// float rollError=0;
// float rollErrorOld;
// float rollErrorChange;
// float rollErrorSlope=0;
// float rollErrorArea=0;
// float rollServoVal;

// void setup() {
//   initMPU();
//   milliNew=millis(); // inital time
// }

// void loop() {
//   rollActual = gyroDataSent.GyroX;
//   milliOld=milliNew;
//   milliNew=millis();
//   dt=milliNew-milliOld;

//   rollErrorOld=rollError;
//   rollError=rollTarget-rollActual;
//   rollErrorChange=rollError-rollErrorOld;
//   rollErrorSlope=rollErrorChange/dt;
//   rollErrorArea=rollErrorArea+rollError*dt;
//   rollServoVal=rollServoVal+kp*rollError+ki*rollErrorSlope+kd*rollErrorArea;
//   rollServo.write(rollServoVal);
// }
// #endif

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
    events.send(getGyroWeb().c_str(),"gyro_readings",millis());
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

// /*Testing external interupt*/
// #if 0 //
// #include <esp32_button.h>

// #define BUTTON_1_PIN 33

// button_t button_1;

// void IRAM_ATTR button_isr()
// {
//   button_update(&button_1);
// }

// void setup()
// {
//   Serial.begin(9600);

//   button_add_default(&button_1, BUTTON_1_PIN);

//   button_init(&button_isr);
// }

// void loop()
// {
//   if (button_1.mode)
//   {
//     // Print modes: 1- Clicked, 2- Double Clicked 3- Long Pressed
//     Serial.println(button_1.mode);

//     // Reset modes
//     button_1.mode = NONE;
//   }
//   else {
//     Serial.println(button_1.mode);
//   }

//   delay(1000);
// }
// #endif

// #if 0
// #include "WiFi.h"
// //----------------------------------------

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   WiFi.mode(WIFI_MODE_STA);
//   Serial.println(WiFi.macAddress());
// }
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID LOOP
// void loop() {
//   // put your main code here, to run repeatedly:

// }
// #endif
