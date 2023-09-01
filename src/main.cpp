#include <Arduino.h>
#include "Motor.h"
#include "Line.h"

Motor motor;
Line line;

void setup() {
   Serial.begin(9600);
   motor.sleep();
}

void loop() {
   line.check();
   // Serial.println(isOnLine);

   if(isOnLine) {
      motor.run(avoidAngle);
      Serial.println(avoidAngle);
   }
   else {
      motor.sleep();
   }
}
