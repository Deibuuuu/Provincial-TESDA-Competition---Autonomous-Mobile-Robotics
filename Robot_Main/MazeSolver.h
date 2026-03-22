#pragma once
#include <Arduino.h>
#include "MecanumCar.h"

enum MazeState {
  STATE_FORWARD,
  STATE_TURN_RIGHT,
  STATE_TURN_LEFT,
  STATE_UTURN,
  STATE_STOP
};

class MazeSolver {
  private:
    int trigFront, echoFront, trigLeft, echoLeft, trigRight, echoRight, trigRear, echoRear;
    int thresholdFront, thresholdLeft, thresholdRight, thresholdRear;
    MecanumCar* robot;
    long getDistance(int trig, int echo);

  public:
    MazeSolver(int tF, int eF, int tL, int eL, int tR, int eR, int tB, int eB, 
               int thF, int thL, int thR, int thB, MecanumCar* carPtr);
    void begin();
    void solveMaze();
    void setIndividualThreshold(int thF, int thL, int thR, int thB);
};