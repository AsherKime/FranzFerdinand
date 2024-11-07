#include <Servo.h>

int servoPin = 3; 
// Create a servo object 
Servo Servo1; 

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(servoPin); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000); 
}
