#include "ForkliftAndClamp.h"

// Forklift Implementation
Forklift::Forklift(int up, int down, int pwm) : liftUpPin(up), liftDownPin(down), speedPin(pwm) {}

void Forklift::begin() {
  pinMode(liftUpPin, OUTPUT); pinMode(liftDownPin, OUTPUT); pinMode(speedPin, OUTPUT);
  stop();
}

void Forklift::moveUp() { digitalWrite(liftUpPin, HIGH); digitalWrite(liftDownPin, LOW); analogWrite(speedPin, 255); }
void Forklift::stop() { digitalWrite(liftUpPin, LOW); digitalWrite(liftDownPin, LOW); }

// Clamp Implementation with Distance Sensor
Clamp::Clamp(int sPin, int oA, int cA, int tP, int eP) : pin(sPin), openA(oA), closedA(cA), trig(tP), echo(eP) {}

void Clamp::begin() {
  servo.attach(pin);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  open();
}

void Clamp::open() { servo.write(openA); }
void Clamp::close() { servo.write(closedA); }

bool Clamp::isObjectPresent(int thresh) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long dist = pulseIn(echo, HIGH) * 0.034 / 2;
  return (dist > 0 && dist < thresh);
}