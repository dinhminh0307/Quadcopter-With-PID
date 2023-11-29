// Define the incoming data, RECEIVED into this board
typedef struct struct_msg_Receive
{
    int Receive_PotValue;
} struct_msg_Receive;

// Define the outgoing data, SENT out from this board
typedef struct struct_msg_Sent
{
    int Sent_PotAngle;
} struct_msg_Sent;

// ******************************************
// Function declaration
// ******************************************
void SerialDataWrite();
void OnDataReceive(const uint8_t *mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
float floatMap(float, float, float, float, float);
void espnow_initialize();