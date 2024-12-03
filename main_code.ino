#include <Servo.h>
#define buttonPin 2
#define servoPin 3
#define s1p1 4
#define s1p2 5
#define s1p3 6
#define s1p4 7
#define s2p1 8
#define s2p2 9
#define s2p3 10
#define s2p4 11
#define ledPin 12


//Stepper Motor Stuff
const int stepsPerRevolution = 2048;


int buttonState = 0;
unsigned long start_time = millis();
unsigned long current_time = millis();
unsigned long time_point;

Servo badGuy; 

void setup() {
  pinMode(buttonPin, INPUT);
  badGuy.attach(servoPin);
  pinMode(s1p1, OUTPUT);
  pinMode(s1p2, OUTPUT);
  pinMode(s1p3, OUTPUT);
  pinMode(s1p4, OUTPUT);
  pinMode(s2p1, OUTPUT);
  pinMode(s2p2, OUTPUT);
  pinMode(s2p3, OUTPUT);
  pinMode(s2p4, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println("Started");
  badGuy.write(0);
  moveSled(false);
  waitTillOn(buttonPin);
  delay(1000);
  moveSled(true);
  badGuy.write(90);
  // read the state of the pushbutton value:
  delay(5000);
  waitTillOffConsistent(buttonPin);
  badGuy.write(0);
  delay(1000);
  moveSled(true);
  //rotateBackground();
  delay(5000);
  waitTillOn(buttonPin);
  moveSled(false);
  delay(4000);
  //rotateBackground();
  digitalWrite(ledPin, 1);
  delay(200);
  digitalWrite(ledPin, 0);
  delay(1000);
  digitalWrite(ledPin, 1);
  delay(200);
  digitalWrite(ledPin, 0);

  
  
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

void runStepper(int stepDelay, int steps, int pin1, int pin2, int pin3, int pin4) {
  int numberOfLoops = steps / 4;
  if (numberOfLoops < 0) {
    for (int i = 0; i > numberOfLoops; i--) {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      delay(stepDelay);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      
    }
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  else {
    for (int i = 0; i < numberOfLoops; i++) {
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      delay(stepDelay);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      delay(stepDelay);
    }
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
}

void rotateBackground() {
  runStepper(4, 1024, s2p1, s2p2, s2p3, s2p4);
  delay(250);
  runStepper(4, -340, s2p1, s2p2, s2p3, s2p4);
}

void moveSled(bool foward) {
  if (foward) {
    runStepper(2, -4048, s1p1, s1p2, s1p3, s1p4);
  }
  else {
    runStepper(2, 4048, s1p1, s1p2, s1p3, s1p4);
  }
}
