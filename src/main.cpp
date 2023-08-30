#include <Arduino.h>
#include "Motor.h"

Motor motor;

int MuxPins[8] = {13,16,20,21,32,33,10,17};
int LineOUT[2] = {11,10};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++) {
    pinMode(MuxPins[i],OUTPUT);
  }
  pinMode(LineOUT[0],INPUT);
  pinMode(LineOUT[1],INPUT);
}

void loop() {
  int MuxCode[2][16][4] = {
    {
    {0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},
    {0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},
    {0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},
    {0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}
  },
  {
    {0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},
    {0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},
    {0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},
    {0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}
  }
  };

  int cnt = 0;
  for(int i = 0; i < 16; i++) {
    int mode = 1;
    digitalWrite(MuxPins[4*mode],MuxCode[mode][cnt][0]);
    digitalWrite(MuxPins[4*mode+1],MuxCode[mode][cnt][1]);
    digitalWrite(MuxPins[4*mode+2],MuxCode[mode][cnt][2]);
    digitalWrite(MuxPins[4*mode+3],MuxCode[mode][cnt][3]);
    Serial.print(analogRead(LineOUT[mode]) > 900);
    Serial.print(" ");
    cnt++;
  }
  Serial.println("");
}
