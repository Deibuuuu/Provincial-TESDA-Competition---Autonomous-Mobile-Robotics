#pragma once
#include <Arduino.h>
#include <Servo.h>

class Forklift {
  private:
    int liftUpPin, liftDownPin, speedPin;
  public:
    Forklift(int up, int down, int pwm);
    void begin();
    void moveUp();
    void moveDown();
    void stop();
};

class Clamp {
  private:
    Servo servo;
    int pin, openA, closedA, trig, echo;
  public:
    Clamp(int sPin, int oA, int cA, int tP, int eP);
    void begin();
    void open();
    void close();
    bool isObjectPresent(int thresh);
};