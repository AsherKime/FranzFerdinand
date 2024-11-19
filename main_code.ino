#include <Servo.h>
const int buttonPin = 2;  // the number of the pushbutton pin
const int servoPin = 3; 

int buttonState = 0;
unsigned long start_time = millis();
unsigned long current_time = millis();
unsigned long time_point;

Servo CarSled; 

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  CarSled.write(0);
  waitTillOn(buttonPin);
  CarSled.write(90);
  Serial.println("Imagine I'm Driving Foward rn");
  delay(3000);
  Serial.println("Woah is that a bomb?!?!?! It blew the second vehicle away!");
  waitTillOffConsistent(buttonPin);
  CarSled.write(180);
  Serial.println("Driving to the major to get away");
  delay(2000);
  Serial.println("Waiting for both cars, facing the other way but I'll go even if they aren't");
  waitTillOn(buttonPin);
  CarSled.write(90);
  Serial.println("This looks like a fun cafe...");

  
  
}

int waitTillOn (int pinNum) {
  while(digitalRead(pinNum) == 0) {
  }
  return 1;
}
int waitTillOffConsistent(int pinNum) {
  while (true) {
    current_time = millis();
    if(digitalRead(pinNum) == 0) {
      if (current_time-time_point > 1000) {
        return 1;
      }
    } else {
      time_point = millis();
    }
  }
}
