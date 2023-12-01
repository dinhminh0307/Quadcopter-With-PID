#include "./Controller.h"

void buttonInit() {
  ESC.attach(escPWM, 1000, 2000);
  ESC2.attach(escPWM2, 1000, 2000);
  // ESC3.attach(escPWM3, 1000, 2000);
  ESC4.attach(escPWM4, 1000, 2000);
  button_add_default(&button_1, BUTTON_1_PIN);
  button_init(&button_isr);
  Serial.begin(115200);
}

void IRAM_ATTR button_isr()
{
  button_update(&button_1);
}

void rotateBLDC(int myVal) {
  int loopCount = 1;
  while (true)
    {
      if (loopCount == 1)
      {
        ESC.write(myVal);
      }
      else if (loopCount == 2)
      {
        ESC2.write(myVal);
      }
      // else if (loopCount == 3)
      // {
      //   ESC3.write(val);
      // }
      else if (loopCount == 4)
      {
        ESC4.write(myVal);
      }
      loopCount++;
      if (loopCount == 5)
      {
        break;
      }
      delay(100);
    }
}