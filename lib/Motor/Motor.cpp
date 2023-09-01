#include "Arduino.h"
#include "Motor.h"

#define MD_F 1000000 // PWM周波数[Hz]

const int MotorPins[4][2] = {{4,5},{8,9},{7,6},{2,3}};
int speed = 180;

Motor::Motor() {
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 2; j++) {
         pinMode(MotorPins[i][j],OUTPUT);
         analogWriteFrequency(MotorPins[i][j],MD_F);
      }
   }
}

void Motor::run(int angle) {
   angle = 450 - angle; // 単位円座標に変換
   const int MotorAngle[4] = {45, 135, 225, 315};
   float MPwrVector[4] = {0};
   float MPwrMax = 0;
   while(angle >= 360) angle -= 360;
   while(angle < 0) angle += 360;
   for(int i = 0; i < 4; i++) {
      MPwrVector[i] = sin((angle - MotorAngle[i]) * (PI / 180));
      if(MPwrMax < MPwrVector[i]) MPwrMax = MPwrVector[i];
   }
   if(MPwrMax < 1) {
      for(int i = 0; i < 4; i++) {
         MPwrVector[i] *= (1 / MPwrMax);
      }
   }
   for(int i = 0; i < 4; i++) {
      int finalPower = speed * MPwrVector[i];
      Motor::roll(i, finalPower);
   }
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
   for(int i = 0; i < 4; i++) {
      analogWrite(MotorPins[i][0],255);
      analogWrite(MotorPins[i][1],255);
   }
}

void Motor::sleep() {
   for(int i = 0; i < 4; i++) {
      analogWrite(MotorPins[i][0],0);
      analogWrite(MotorPins[i][1],0);
   }
}