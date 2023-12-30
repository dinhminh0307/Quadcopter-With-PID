#include <ESPnow.h>
#include <PID.h>

// variable declare

joystick_struct_receiver joystickSignalReceiver;
voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;
cal_signal_receive calSignalReceiver;
tunning_struct_receive tunningReceiver;
// pid_tunning_command_rcv tunningCommandReceive;

uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x17, 0x21, 0xC4}; // mac address of remote

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
    esp_now_peer_info_t peerInfo = {};
    esp_now_register_send_cb(onDataSent); // call back function to getthe sent status into the  ondatasent
    esp_now_register_recv_cb(onDataReceived);
    memcpy(peerInfo.peer_addr, broadcastAddress, sizeof(broadcastAddress));
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    //----------------------------------------

    //----------------------------------------Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    else
    {
        Serial.println("succssefull to add peer");
        return;
    }
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    // Serial.println("send here");
}

void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len)
{

    switch (len)
    {
    case sizeof(recieved_Voltage):

        memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
        Serial.println(recieved_Voltage.voltageVal);
        break;
        // case sizeof(tunningCommandReceive):
        //     memcpy(&tunningCommandReceive, incomingData, sizeof(tunningCommandReceive));
        //     Serial.println(tunningCommandReceive.charRcv);
        //     break;

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
    case sizeof(tunningReceiver):
        memcpy(&tunningReceiver, incomingData, sizeof(tunningReceiver));
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
