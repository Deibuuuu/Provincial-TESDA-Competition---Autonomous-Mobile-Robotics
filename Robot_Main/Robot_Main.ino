#include "MecanumCar.h"
#include "ForkliftAndClamp.h"
#include "MazeSolver.h"

// --- Hardware Initialization for Arduino MEGA ---

// Motors: (FL_EN, FL_IN1, FL_IN2, FR_EN, FR_IN1, FR_IN2, RL_EN, RL_IN1, RL_IN2, RR_EN, RR_IN1, RR_IN2)
MecanumCar myRobot(5, 7, 8,      // Front-Left
                   6, 11, 24,    // Front-Right
                   9, 22, 23,    // Rear-Left
                   10, A4, A5);  // Rear-Right

// Forklift: (Up_Pin, Down_Pin, PWM_Pin)
Forklift myForklift(A0, A1, A2);

// Clamp: (Servo_Pin, Open_Angle, Closed_Angle, Trig_Pin, Echo_Pin)
Clamp myClamp(A6, 120, 10, 36, 37);

// Maze Solver: (TrigF, EchoF, TrigL, EchoL, TrigR, EchoR, TrigB, EchoB, RobotPointer)

MazeSolver myMazeSolver(26, 27, 28, 29, 30, 31, 32, 33, 
                                0, 0, 0, 0, &myRobot);

// --- Manual Movement Helpers (by cm) ---
// Calibration factor (adjust based on real-world testing)
// e.g., if the robot moves 20cm in 1000ms at speed 150, this is 20.0
const float CM_PER_SECOND = 20.0;
const float DEGREES_PER_SECOND = 180.0;

void moveForwardCM(float cm) {
  unsigned long delayTime = (cm / CM_PER_SECOND) * 1000;
  myRobot.forward();
  delay(delayTime);
  myRobot.stop();
}

void moveBackwardCM(float cm) {
  unsigned long delayTime = (cm / CM_PER_SECOND) * 1000;
  myRobot.backward();
  delay(delayTime);
  myRobot.stop();
}

void turnLeftDegrees(float degrees) {
  unsigned long delayTime = (degrees / DEGREES_PER_SECOND) * 1000;
  myRobot.turnLeft();
  delay(delayTime);
  myRobot.stop();
}

void turnRightDegrees(float degrees) {
  unsigned long delayTime = (degrees / DEGREES_PER_SECOND) * 1000;
  myRobot.turnRight();
  delay(delayTime);
  myRobot.stop();
}

void setup() {
  Serial.begin(9600);
  
  myRobot.setIndividualSpeeds(150, 150, 150, 150);
  myRobot.setStrafeSpeed(150);
  //myRobot.setIndividualSpeeds(int fl, int fr, int rl, int rr)
  myRobot.setTrim(0.95, 1.0, 1.0, 1.0);
  myForklift.begin();
  myClamp.begin();
  myMazeSolver.begin();
  myMazeSolver.setIndividualThreshold(15, 25, 25, 15);
 
  
}

void loop() {
  // 1. Check for objects to grab using ultrasonic sensor
  if (myClamp.isObjectPresent(10)) { // 10cm threshold
    myRobot.stop();
    myClamp.close();
    delay(500);
    myForklift.moveUp();
    delay(1000);
    myForklift.stop();
  } 
  // 2. Otherwise, manual movement
  else {

    // ---- MANUAL MOVEMENT COMMANDS ----
    // Adjust cm values as needed. Example: move forward 10 cm
    moveForwardCM(10.0);
    delay(2000); // pause
    
    // NOTE: To switch back to maze solving, comment out the manual 
    // movement lines above, and uncomment the line below. Do not remove maze solver code!
    // myMazeSolver.solveMaze();
  }
  


}