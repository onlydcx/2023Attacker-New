#include "Arduino.h"
#include "Line.h"

extern int avoidAngle;
int avoidAngle;
extern bool isOnLine;
bool isOnLine;

int threshold = 900;

const int MuxPins[8] = {13,16,20,21,32,33,10,17};
const int LineOUT[2] = {11,10};
// センサ配置 16,17,...,31,0,1,...,15
const int LineMuxID[2][16][4] = {
    {
        {1,1,1,1},{0,1,1,1},{1,0,1,1},{0,0,1,1},
        {1,1,0,1},{0,1,0,1},{1,0,0,1},{0,0,0,1},
        {1,1,1,0},{0,1,1,0},{1,0,1,0},{0,0,1,0},
        {1,1,0,0},{0,1,0,0},{1,0,0,0},{0,0,0,0}
    },
    {
        {1,1,1,1},{0,1,1,1},{1,0,1,1},{0,0,1,1},
        {1,1,0,1},{0,1,0,1},{1,0,0,1},{0,0,0,1},
        {1,1,1,0},{0,1,1,0},{1,0,1,0},{0,0,1,0},
        {1,1,0,0},{0,1,0,0},{1,0,0,0},{0,0,0,0}
        // {0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},
        // {0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},
        // {0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},
        // {0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}
    }
};

float ChipInfo[32][3] = {0};

Line::Line() {
    for(int i = 0; i < 32; i++) {
        ChipInfo[i][0] = i * (float)11.25;
        ChipInfo[i][1] = sin(ChipInfo[i][0] * (PI / 180));
        ChipInfo[i][2] = cos(ChipInfo[i][0] * (PI / 180));
    }
    for(int i = 0; i < 8; i++) {
        pinMode(MuxPins[i],OUTPUT);
    }
    pinMode(LineOUT[0],INPUT);
    pinMode(LineOUT[1],INPUT);
}

void Line::check() {
    int linecnt = 0;
    float _v[2] = {0};
    // int i = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 16; j++) { // 32??
            digitalWrite(MuxPins[4*i+0],LineMuxID[i][j][0]);
            digitalWrite(MuxPins[4*i+1],LineMuxID[i][j][1]);
            digitalWrite(MuxPins[4*i+2],LineMuxID[i][j][2]);
            digitalWrite(MuxPins[4*i+3],LineMuxID[i][j][3]);
            if(analogRead(LineOUT[i]) > threshold) {
                // Serial.print(ChipInfo[(i*16)+j][2]);
                linecnt++;
                _v[0] += ChipInfo[(i*16)+j][1]; // sin
                _v[1] += -ChipInfo[(i*16)+j][2]; // cos
            }
            // Serial.print(analogRead(LineOUT[i]) > 900);
            // Serial.print(" ");
        }
    }
    // Serial.println(_v[0]);
    if((_v[0] != 0) && (_v[1] != 0) && (linecnt > 0)) {
        avoidAngle = atan2(_v[1],_v[0]) * (180 / PI);
        isOnLine = true;
    }
    else {
        isOnLine = false;
    }
    // Serial.println("");
}