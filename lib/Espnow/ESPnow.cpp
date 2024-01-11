#include <ESPnow.h>

// variable declare

joystick_struct_receiver joystickSignalReceiver;
voltage_struct_receive recieved_Voltage;
button_struct_receive received_Button;
cal_signal_receive calSignalReceiver;
tunning_struct_receive tunningReceiver;
button_struct_send buttonSender;
imu_calibrate_send imuCalStatus;
yaw_struct_receive yaw_signal_receiver;
int isStop;
// pid_tunning_command_rcv tunningCommandReceive;

uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x17, 0x21, 0xC4}; // mac address of remote

void Init_ESPnow()
{
    isStop = 300;
    imuCalStatus.status = 200;
    yaw_signal_receiver.yawState = YAW_NEUTRAL_STATE;
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
}

void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len)
{

    switch (len)
    {
    case sizeof(recieved_Voltage):

        memcpy(&recieved_Voltage, incomingData, sizeof(recieved_Voltage));
        Serial.println(recieved_Voltage.voltageVal);
        break;
    case sizeof(calSignalReceiver):

        memcpy(&calSignalReceiver, incomingData, sizeof(calSignalReceiver));
        break;

    case sizeof(joystickSignalReceiver):

        memcpy(&joystickSignalReceiver, incomingData, sizeof(joystickSignalReceiver));

        // Rest of your joystick handling code...
        if (joystickSignalReceiver.y <= 12 && joystickSignalReceiver.y > 5 && joystickSignalReceiver.x == 5)
        {

            // Moving forward
            angley_setpoint = -15;
            anglex_setpoint = 0;
        }
        else if (joystickSignalReceiver.y >= 0 && joystickSignalReceiver.y < 5 && joystickSignalReceiver.x == 5)
        {
            // Moving backward
            angley_setpoint = 15;
            anglex_setpoint = 0;
        }
        else if (joystickSignalReceiver.y == 5 && joystickSignalReceiver.x >= 0 && joystickSignalReceiver.x < 5)
        {
            // Rolling right
            anglex_setpoint = 20;
            angley_setpoint = 0;
        }
        else if (joystickSignalReceiver.y == 5 && joystickSignalReceiver.x >5  && joystickSignalReceiver.x <= 12)
        {
            // Rolling left
            anglex_setpoint = -20;
            angley_setpoint = 0;
        }
        else
        {
            // Hover
            angley_setpoint = 0;
            anglex_setpoint = 0;
        }

        Serial.println(anglex_setpoint);
        Serial.println(angley_setpoint);
        Serial.println(anglez_setpoint);
        Serial.println(joystickSignalReceiver.y);
        Serial.println(joystickSignalReceiver.x);

        break;
    case sizeof(tunningReceiver):
        memcpy(&tunningReceiver, incomingData, sizeof(tunningReceiver));
        if (tunningReceiver.tunningState == 0)
        {

            resetTunning();
        }
        else
        {
            setNewPIValue();
        }

        break;
    case sizeof(received_Button):
        memcpy(&received_Button, incomingData, sizeof(received_Button));
        Serial.println("set stop");
        isStop = received_Button.state;
        break;
    case sizeof(yaw_signal_receiver):
        memcpy(&yaw_signal_receiver, incomingData, sizeof(yaw_signal_receiver));
        if (yaw_signal_receiver.yawState == YAW_LEFT_STATE)
        {
            Serial.print("Yaw state: ");
            Serial.println(yaw_signal_receiver.yawState);
            anglez_setpoint -= 20;

            yaw_signal_receiver.yawState = YAW_NEUTRAL_STATE;
        }
        else if (yaw_signal_receiver.yawState == YAW_RIGHT_STATE)
        {
            Serial.print("Yaw state: ");
            Serial.println(yaw_signal_receiver.yawState);
            anglez_setpoint += 20;

            yaw_signal_receiver.yawState = YAW_NEUTRAL_STATE;
        }
        else
        {
            anglez_setpoint = 0;
        }
        Serial.print("angle set point z: ");
        Serial.println(anglez_setpoint);
        break;
    default:
        // Handle unexpected data length
        Serial.println("Received data of unexpected length.");
        break;
    }
}

void resetTunning()
{

    kpY = 1.25;
    kdY = 0.006;
    kiY = 0.015;

    // tunning for pitch axis
    kpX = 0.95;
    kdX = 0.013;
    kiX = 0.015;

    // tunning for yaw axis
    kpZ = 0.75;
    kdZ = 0.00;
    kiZ = 0.00;
    sendPIDValue();
}

void setNewPIValue()
{
    Serial.println("New tunning is set");
    kpX = tunningReceiver.kpRoll;
    kdX = tunningReceiver.kdRoll;
    kiX = tunningReceiver.kiRoll;

    kpY = tunningReceiver.kpPitch;
    kdY = tunningReceiver.kdPitch;
    kiY = tunningReceiver.kiPitch;

    kpZ = tunningReceiver.kpYaw;
    kdZ = tunningReceiver.kdYaw;
    kiZ = tunningReceiver.kiYaw;
    sendPIDValue();
}

void sendPIDValue()
{
    tunning_struct_send pid_info_send;
    // Serial.print("send kpy: ");
    // Serial.print(kpY);
    // Serial.print(" send kdy: ");
    // Serial.print(kdY);
    // Serial.print(" send kiy: ");
    // Serial.println(kiY);

    // Serial.print("send kpx: ");
    // Serial.print(kpX);
    // Serial.print(" send kdx: ");
    // Serial.print(kdX);
    // Serial.print(" send kix: ");
    // Serial.println(kiX);

    // Serial.print("send kpz: ");
    // Serial.print(kpZ);
    // Serial.print(" send kdz: ");
    // Serial.print(kdZ);
    // Serial.print(" send kiz: ");
    // Serial.println(kiZ);
    pid_info_send.kpPitch = kpY;
    pid_info_send.kdPitch = kdY;
    pid_info_send.kiPitch = kiY;

    pid_info_send.kpRoll = kpX;
    pid_info_send.kdRoll = kdX;
    pid_info_send.kiRoll = kiX;

    pid_info_send.kpYaw = kpZ;
    pid_info_send.kdYaw = kdZ;
    pid_info_send.kiYaw = kiZ;

    esp_now_send(broadcastAddress, (uint8_t *)&pid_info_send, sizeof(pid_info_send));
}
