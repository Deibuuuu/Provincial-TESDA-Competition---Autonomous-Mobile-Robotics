#include "MazeSolver.h"

MazeSolver::MazeSolver(int tF, int eF, int tL, int eL, int tR, int eR, int tB, int eB, 
                       int thF, int thL, int thR, int thB, MecanumCar* carPtr) {
  trigFront = tF; echoFront = eF;
  trigLeft = tL;  echoLeft = eL;
  trigRight = tR; echoRight = eR;
  trigRear = tB;  echoRear = eB; 
  
  thresholdFront = thF;
  thresholdLeft = thL;
  thresholdRight = thR;
  thresholdRear = thB;
  
  robot = carPtr;
}

void MazeSolver::begin() {
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT);  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT); pinMode(echoRight, INPUT);
  pinMode(trigRear, OUTPUT);  pinMode(echoRear, INPUT); 
}

long MazeSolver::getDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // 30ms timeout prevents loop freezing. If timeout (0), assume clear path.
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999;
  
  return duration * 0.034 / 2;
}

void MazeSolver::setIndividualThreshold(int thF, int thL, int thR, int thB) {
  thresholdFront = thF;
  thresholdLeft = thL;
  thresholdRight = thR;
  thresholdRear = thB;
}

void MazeSolver::solveMaze() {
  long dF = getDistance(trigFront, echoFront);
  delay(30); // Prevent echo interference from the previous sensor
  long dL = getDistance(trigLeft, echoLeft);
  delay(30);
  long dR = getDistance(trigRight, echoRight);
  delay(30);
  long dB = getDistance(trigRear, echoRear);
  delay(30);

  // Print values for debugging distance readings on the Serial Monitor
  Serial.print("Front: "); Serial.print(dF);
  Serial.print(" cm | Left: "); Serial.print(dL);
  Serial.print(" cm | Right: "); Serial.print(dR);
  Serial.print(" cm | Rear: "); Serial.print(dB);
  Serial.println(" cm");

  bool wallFront = (dF <= thresholdFront);
  bool wallRight = (dR <= thresholdRight);
  bool wallLeft  = (dL <= thresholdLeft);
  bool wallRear  = (dB <= thresholdRear);

  // 1. Evaluate State
  MazeState nextState;
  
  if (!wallRight) {
    nextState = STATE_TURN_RIGHT;
  } else if (!wallFront) {
    nextState = STATE_FORWARD;
  } else if (!wallLeft) {
    nextState = STATE_TURN_LEFT;
  } else if (!wallRear) {
    nextState = STATE_UTURN;
  } else {
    nextState = STATE_STOP;
  }

  // 2. Execute Finite State Machine
  switch (nextState) {
    case STATE_TURN_RIGHT:
      // 1.5 Second delay before executing the movement
      robot->stop();
      delay(1500);
      robot->turnRight();
      delay(500); // Tune this delay for a ~90 degree turn
      robot->stop();
      delay(100);
      robot->forward();
      delay(500); // Move forward into the new corridor slightly
      break;

    case STATE_FORWARD:
      {
        // Proportional wall following
        int targetDistance = 10;
        int error = dR - targetDistance; 
        
        float kp = 6.0; 
        int correction = (int)(error * kp); 
        
        // Base speed updated to match setup() speed
        int baseSpeed = 150; 
        
        int leftSpeed = constrain(baseSpeed + correction, 0, 255);
        int rightSpeed = constrain(baseSpeed - correction, 0, 255);
        
        robot->setIndividualSpeeds(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
      }
      break;

    case STATE_TURN_LEFT:
      // 1.5 Second delay before executing the movement
      robot->stop();
      delay(1500);
      robot->turnLeft();
      delay(500); // Tune this delay for a ~90 degree turn
      break;

    case STATE_UTURN:
      // 1.5 Second delay before executing the movement
      robot->stop();
      delay(1500);
      robot->turnRight();
      delay(1000); // Tune this delay for a ~180 degree turn
      break;

    case STATE_STOP: // Boxed in entirely
      robot->stop();
      break;
  }
}