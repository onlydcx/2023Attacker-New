#include "Arduino.h"
#include "Line.h"

extern int avoidAngle;
int avoidAngle;
extern bool isOnLine;
bool isOnLine;
int a = 700;
const int threshold[2][16] = {
    {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a},
    {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a}
    // {676, 517, 519, 518, 518, 518, 520, 520, 519, 519, 518, 520, 520, 520, 520, 518},
    // {519, 518, 519, 519, 516, 518, 518, 519, 519, 518, 517, 518, 512, 518, 518, 518}
};

const int MuxPins[8] = {13,16,20,21,32,33,10,17};
const int LineOUT[2] = {11,10};
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

int LineTh[2][16] = {0};
int LineThMin[2][16] = {1023};
int LineThMax[2][16] = {0};

void Line::ThUpDate() {
    Serial.println("Start");
    int time = millis();
    while((millis() - time) < 4000) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 16; j++) {
                digitalWrite(MuxPins[4*i+0],LineMuxID[i][j][0]);
                digitalWrite(MuxPins[4*i+1],LineMuxID[i][j][1]);
                digitalWrite(MuxPins[4*i+2],LineMuxID[i][j][2]);
                digitalWrite(MuxPins[4*i+3],LineMuxID[i][j][3]);
                int val = analogRead(LineOUT[i]);
                // Serial.print(val);
                // Serial.print(" ");
                if(val > LineThMax[i][j]) LineThMax[i][j] = val;
                if(val < LineThMin[i][j]) LineThMin[i][j] = val;
            }
        }
        // Serial.println("");
    }
    for(int i = 0; i < 2; i++) {
        Serial.print("{");
        for(int j = 0; j < 16; j++) {
            LineTh[i][j] = LineThMax[i][j] - ((LineThMax[i][j] - LineThMin[i][j]) / 3);
            Serial.print(LineTh[i][j]);
            if(j != 15) Serial.print(", ");
        }
        if(i == 0) Serial.println("},");
        else Serial.print("}");
    }
    while(1) {}
}

void Line::check() {
    int linecnt = 0;
    float _v[2] = {0};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 16; j++) {
            digitalWrite(MuxPins[4*i+0],LineMuxID[i][j][0]);
            digitalWrite(MuxPins[4*i+1],LineMuxID[i][j][1]);
            digitalWrite(MuxPins[4*i+2],LineMuxID[i][j][2]);
            digitalWrite(MuxPins[4*i+3],LineMuxID[i][j][3]);
            if(analogRead(LineOUT[i]) > threshold[i][j]) {
                linecnt++;
                // Serial.print((i*16)+j);
                _v[0] += ChipInfo[(i*16)+j][1]; // sin
                _v[1] += -ChipInfo[(i*16)+j][2]; // cos
            }
            Serial.print(threshold[i][j]);
            Serial.print(" ");
        }
    }
    if((_v[0] != 0) && (_v[1] != 0) && (linecnt > 0)) {
        avoidAngle = atan2(_v[1],_v[0]) * (180 / PI);
        isOnLine = true;
    }
    else {
        isOnLine = false;
    }
    Serial.println("");
}