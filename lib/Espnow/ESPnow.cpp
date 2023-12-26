#include <ESPnow.h>
#include <PID.h>

// variable declare

joystick_struct_receiver joystickSignalReceiver;
voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;
cal_signal_receive calSignalReceiver;
pid_tunning_command_rcv tunningCommandReceive;

uint8_t broadcastAddress[] = {0x48, 0xE7, 0x29, 0x96, 0xBB, 0x18}; // mac address of remote

void Init_ESPnow()
{

    WiFi.mode(WIFI_STA);
    // Initilize ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    // Register callback function
    esp_now_register_recv_cb(onDataReceived);
}

void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len)
{

    switch (len)
    {
    case sizeof(recieved_Voltage):

        memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
        Serial.println(recieved_Voltage.voltageVal);
        break;
    
    case sizeof(tunningCommandReceive):
        memcpy(&tunningCommandReceive, incomingData, sizeof(tunningCommandReceive));
        Serial.println(tunningCommandReceive.charRcv);
        break;

    case sizeof(calSignalReceiver):

        memcpy(&calSignalReceiver, incomingData, sizeof(calSignalReceiver));
        break;

    case sizeof(joystickSignalReceiver):

        memcpy(&joystickSignalReceiver, incomingData, sizeof(joystickSignalReceiver));

        // Rest of your joystick handling code...
        if (joystickSignalReceiver.y > 6 && joystickSignalReceiver.x == 5)
        {
            Get_accelgyro();

            // Moving forward
            gyrox_setpoint = 30; // in degree
            gyroy_setpoint = 0;
            gyroz_setpoint = 0;
        }
        else if (joystickSignalReceiver.y < 6)
        {
            // Moving backward
            gyrox_setpoint = -30;
            gyroy_setpoint = 0;
            gyroz_setpoint = 0;
        }
        else
        {
            // Hover
            gyrox_setpoint = 0;
            gyroy_setpoint = 0;
            gyroz_setpoint = 0;
        }

        if (joystickSignalReceiver.x > 6)
        {
            // Rolling right
            gyrox_setpoint = 0;
            gyroy_setpoint = 30;
            gyroz_setpoint = 0;
        }
        else if (joystickSignalReceiver.x < 6)
        {
            // Rolling left
            gyrox_setpoint = 0;
            gyroy_setpoint = -30;
            gyroz_setpoint = 0;
        }
        else
        {
            // Hover
            gyrox_setpoint = 0;
            gyroy_setpoint = 0;
            gyroz_setpoint = 0;
        }
        break;

    default:
        // Handle unexpected data length
        Serial.println("Received data of unexpected length.");
        break;
    }
    // if (len == sizeof(received_Button))
    // { // receive button data
    //   memcpy(&received_Button, incomingData, sizeof(received_Button));
    //   if(received_Button.state == YAW_LEFT)
    //   {
    //      //handle
    //   }
    //   else if (recived_Button.state == YAW_RIGHT)
    //   {

    //   }
    // }
}
