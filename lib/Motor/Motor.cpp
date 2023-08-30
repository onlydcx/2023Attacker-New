#include "Arduino.h"
#include "Motor.h"

#define MD_F 1000000 // PWM周波数[Hz]

int MotorPins[4][2] = {{4,5},{8,9},{7,6},{2,3}};

Motor::Motor() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 2; j++) {
      pinMode(MotorPins[i][j],OUTPUT);
      analogWriteFrequency(MotorPins[i][j],MD_F);
    }
  }
}

void Motor::run(int angle) {

}

void Motor::roll(int num, int power) {
    if(power < 0) {
      analogWrite(MotorPins[num][0],abs(power));
      analogWrite(MotorPins[num][1],0);
    }
    else if(power > 0) {
      analogWrite(MotorPins[num][0],0);
      analogWrite(MotorPins[num][1],abs(power));
    }
    else {
        analogWrite(MotorPins[num][0],255);
        analogWrite(MotorPins[num][1],255);
    }
}

void Motor::stop() {

}

void Motor::free() {

}