#include "MecanumCar.h"
#include "ForkliftAndClamp.h"

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

// HC-05 Bluetooth Config
#define BT_SERIAL Serial1 // MEGA Hardware Serial 1 (TX1: Pin 18, RX1: Pin 19)

void setup() {
  Serial.begin(9600);     // For PC Serial Monitor Debugging
  BT_SERIAL.begin(9600);  // For HC-05 Bluetooth Module
  
  myRobot.setIndividualSpeeds(150, 150, 150, 150);
  myRobot.setStrafeSpeed(150);
  myRobot.setTrim(0.95, 1.0, 1.0, 1.0);
  
  myForklift.begin();
  myClamp.begin();
  
  Serial.println("Bluetooth Remote Control Robot Initialized.");
  Serial.println("Listening for commands on HC-05 (Serial1)...");
  
  // NOTE: MazeSolver logic is completely omitted in this Bluetooth branch.
}

void loop() {
  // Check if a command has been received from Bluetooth
  if (BT_SERIAL.available() > 0) {
    char cmd = BT_SERIAL.read();
    
    // Echo back to Serial monitor for debugging
    Serial.print("Received Command: ");
    Serial.println(cmd);
    
    switch (cmd) {
      // --- MECANUM MOVEMENT ---
      case 'F': myRobot.forward();     break; // Forward
      case 'B': myRobot.backward();    break; // Backward
      case 'L': myRobot.turnLeft();    break; // Turn Left
      case 'R': myRobot.turnRight();   break; // Turn Right
      case 'Q': myRobot.strafeLeft();  break; // Strafe Left
      case 'E': myRobot.strafeRight(); break; // Strafe Right
      case 'S': myRobot.stop();        break; // Stop Movement
      
      // --- FORKLIFT CONTROL ---
      case 'U': myForklift.moveUp();   break; // Forklift Up
      case 'D': myForklift.moveDown(); break; // Forklift Down
      case 'u': // Lowercase to stop both directions
      case 'd': myForklift.stop();     break; // Stop Forklift
      
      // --- CLAMP CONTROL ---
      case 'O': myClamp.open();        break; // Open Clamp
      case 'C': myClamp.close();       break; // Close Clamp
    }
  }
}