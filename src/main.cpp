#include <Arduino.h>
#include <Serial.h>
#include <MPU.h>
#include <Drone.h>
#include <ESPnow.h>
#include <GPS.h>
// #include <GoogleSheet.h>
#include <PID.h>

// void tunningPID();

void setup()
{
  Init_Serial();
  // Init_Serial2(); // for the gps
  Init_ESPnow();
  Init_ESC();
  Init_MPU();
  Init_Serial2(); // for the gps
  // Init_GoogleSheet();

  // Init_PID();
}

void loop()
{

  // Compute_PID();
  Get_MPUangle();
  Compute_PID();
  rotateBLDC();
  // recordGPStoGoogleSheet();
  SerialDataPIDPrint();
  // tunningPID();
  // Serial.println("in loop");
}

// ================================================================
// Function to tune the PID parameters. For example:
// To change the P value to 10, type p10
// To change the I value to -5, type i-5
// To change the D value to 2.4, type d2.4
// To change the setpoint to 3, type s3
// void tunningPID()
// {
//   static String received_chars;
//   Serial.println("Please select tunning option");
//   while (!Serial.available())
//   {
//     char inChar = (char)Serial.read();
//     received_chars += inChar;
//     if (inChar == '\n')
//     {
//       switch (received_chars[0])
//       {
//       case 'p':

//         received_chars.remove(0, 1);
//         kp = received_chars.toFloat();
//         break;
//       case 'i':
//         received_chars.remove(0, 1);
//         ki = received_chars.toFloat();
//         break;
//       case 'd':
//         received_chars.remove(0, 1);
//         kd = received_chars.toFloat();
//         break;
//       case 's':
//         received_chars.remove(0, 1);
//         anglex_setpoint = received_chars.toFloat();
//       default:
//         break;
//       }
//       received_chars = "";
//     }
//   }
// }
