#include "./Drone.h"

void Drone::droneInit() {
    this->potPin1 = 4;
    this->motorPin1 = 18;
    ESC.attach(motorPin1, 1000, 2000);
    this->speedVal = 0;
}

void Drone::btnInit() {
    this->forwardButton = 27;
    this->leftButton = 26;
    this->rightButton = 25;
    this->downButton = 33;

    pinMode(this->forwardButton, INPUT_PULLUP);
    pinMode(this->leftButton, INPUT_PULLUP);
    pinMode(this->rightButton, INPUT_PULLUP);
    pinMode(this->downButton, INPUT_PULLUP);
}

void Drone::controlESC() {
    this->speedVal = analogRead(potPin1);
    this->speedVal = map(this->speedVal, 0, 4095, 0, 180);
    ESC.write(this->speedVal);
}