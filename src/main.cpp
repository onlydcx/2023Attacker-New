#include <Arduino.h>
#include "Motor.h"

Motor motor;

int MuxPins[8] = {13,16,20,21,32,33,10,17};
int LineOUT[2] = {10,11};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++) {
    pinMode(i,OUTPUT);
  }
  pinMode(LineOUT[0],INPUT);
  pinMode(LineOUT[1],INPUT);
}

// D49 [0,0,0,0,0,0,0,0] 0

void loop() {
  for(int i = 0; i < 8; i++) {
    digitalWrite(MuxPins[i],LOW);
  }
  Serial.println(analogRead(LineOUT[0]));
  // for(int i = 0; i < 4; i++) {
  //   motor.roll(i,180);
  // }
}
