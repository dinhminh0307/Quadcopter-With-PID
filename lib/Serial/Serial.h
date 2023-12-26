#include <Arduino.h>
#include <GPS.h>
#include <MPU.h>
#include <PID.h>
unsigned long time_prev = 0;

void Init_Serial()
{
  Serial.begin(115200);
  while (!Serial)
    ;
}

void Init_Serial2()
{
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);
  while (!Serial2)
    ;
}

// ================================================================
void SerialDataMPUPrint()
{
  if (micros() - time_prev >= 20000)
  {
    time_prev = micros();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(anglex);
    Serial.print("\t");
    Serial.print(angley);
    Serial.print("\t");
    Serial.print(anglez);
    Serial.print("\t");
    Serial.print(gyrox);
    Serial.print("\t");
    Serial.print(gyroy);
    Serial.print("\t");
    Serial.print(gyroz);
    Serial.println();
  }
}

void SerialDataPIDPrint()
{
  if (micros() - time_prev >= 50000)
  {
    time_prev = micros();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(anglex);
    Serial.print("\t");
    Serial.print(motor_cmd);
    Serial.print("\t");
    Serial.print(kpX);
    Serial.print("\t");
    Serial.print(kpY);
    Serial.print("\t");
    Serial.print(kpZ);
    Serial.print("\t");
    Serial.print(anglex_setpoint);

    Serial.println();
  }
}
