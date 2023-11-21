#include "./Drone.h"
volatile bool landState;
void Drone::droneInit() {
    this->potPin1 = 4;
    this->motorPin1 = 18;
    ESC.attach(motorPin1, 1000, 2000);
    this->speedVal = 0;
}

void Drone::btnInit() {
    this->landBtn = 33;
    pinMode(this->landBtn, INPUT_PULLUP);
}
void  IRAM_ATTR ISR() {
    landState = true;
}

void Drone::setInterupt() {
    attachInterrupt(this->landBtn, ISR, FALLING);
}

void Drone::controlESC() {
    this->speedVal = analogRead(potPin1);
    this->speedVal = map(this->speedVal, 0, 4095, 0, 180);
    ESC.write(this->speedVal);
}

void Drone::stopDrone(bool state) {
    if(state) {
        for(int i = speedVal; i > 0; i--) {
            ESC.write(i);
        }
    }
}