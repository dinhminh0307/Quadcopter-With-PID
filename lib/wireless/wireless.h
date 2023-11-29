#include <esp_now.h>

// Define the incoming data, RECEIVED into this board
typedef struct struct_msg_Receive_Joystick
{
    int joystickX;
    int joystickY;
} struct_msg_Receive_Joystick;

typedef struct struct_msg_Receive_JTButton
{
    bool pressed;
} struct_msg_Receive_JTButton;

typedef struct struct_msg_Receive_POT
{
    int value;
} struct_msg_Receive_POT;

// ******************************************
// Function declaration
// ******************************************
void espnow_initialize();