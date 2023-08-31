#include "Arduino.h"
#include "Line.h"

int MuxPins[8] = {13,16,20,21,32,33,10,17};
int LineOUT[2] = {11,10};

const int LineMuxID[2][16][4] = {
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

Line::Line() {
  for(int i = 0; i < 8; i++) {
    pinMode(MuxPins[i],OUTPUT);
  }
  pinMode(LineOUT[0],INPUT);
  pinMode(LineOUT[1],INPUT);
}

void Line::check() {
    for(int i = 0; i < 16; i++) {
        int mode = 1;
        digitalWrite(MuxPins[4*mode+0],LineMuxID[mode][i][0]);
        digitalWrite(MuxPins[4*mode+1],LineMuxID[mode][i][1]);
        digitalWrite(MuxPins[4*mode+2],LineMuxID[mode][i][2]);
        digitalWrite(MuxPins[4*mode+3],LineMuxID[mode][i][3]);
        Serial.print(analogRead(LineOUT[mode]));
        Serial.print(" ");
    }
    Serial.println("");
}