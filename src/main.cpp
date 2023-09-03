#include <Arduino.h>
#include "Motor.h"
#include "Line.h"

// Motor motor;
// Line line;

int mux[16][4] = {
   {1,1,1,1},{0,1,1,1},{1,0,1,1},{0,0,1,1},
   {1,1,0,1},{0,1,0,1},{1,0,0,1},{0,0,0,1},
   {1,1,1,0},{0,1,1,0},{1,0,1,0},{0,0,1,0},
   {1,1,0,0},{0,1,0,0},{1,0,0,0},{0,0,0,0}
};

void setup() {
   Serial.begin(9600);
   // motor.sleep();
   // pinMode(26,OUTPUT);
   pinMode(31,OUTPUT);
   pinMode(30,OUTPUT);
   pinMode(29,OUTPUT);
   pinMode(28,OUTPUT);
   pinMode(27,INPUT);
   // pinMode(13,INPUT);
   // digitalWrite(26,LOW);
   // delay(500);
   // digitalWrite(26,HIGH);
   // delay(200);
   // digitalWrite(26,LOW);
}

void loop() {

   for(int j = 0; j < 16; j++) {
      digitalWrite(31,mux[j][0]);
      digitalWrite(30,mux[j][1]);
      digitalWrite(29,mux[j][2]);
      digitalWrite(28,mux[j][3]);
      // delay(10);
      int val = analogRead(A13);
      // int val = pulseIn(27,LOW,833);

      Serial.print(val);
      Serial.print(" ");
   }
   Serial.println("");


   // Serial.println(analogRead(A10));
   // line.check();
   // Serial.println(isOnLine);

   // // if(isOnLine) {
   // //    motor.run(avoidAngle);
   // // }
   // // else {
   // //    motor.stop();
   // // }
}
 