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
   Serial.println(isOnLine);
   // Serial.println(line.check());
   // motor.run(225);

   if(isOnLine) {
      motor.run(avoidAngle);
   }
   else {
      motor.stop();
   }

   // Serial.println(avoidAngle);
   // delay(10);
}
