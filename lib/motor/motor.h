#define MAX_SIGNAL 2000 // Parameter required for the ESC definition
#define MIN_SIGNAL 1000 // Parameter required for the ESC definition
#define MOTOR_PIN_1 33   // Pin 13 attached to the ESC signal pin

void Init_ESC();
void runningMotor1(int CtrlPWM);