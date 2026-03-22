# Autonomous Mobile Robotics - Main Branch (Maze Solver & Manual Movement)

This is the primary branch for the Autonomous Mobile Robotics project. It contains the logic for the autonomous **Maze Solver** using multiple ultrasonic sensors, as well as functions for **Manual Distance-based Movement**.

## Features
- **Maze Solver**: Complete wall-following logic, capable of navigating mazes autonomously using Front, Left, Right, and Rear ultrasonic sensors.
- **Manual Movement**: Helper functions (`moveForwardCM`, `turnLeftDegrees`, etc.) to move the robot by exact centimeters instead of time.
- **Object Grabbing**: The clamp closes and the forklift rises automatically when the clamp's ultrasonic sensor detects an object within 10cm.

## Hardware Setup (Arduino MEGA)
The robot utilizes a custom `MecanumCar` and `ForkliftAndClamp` class structure to manage the motor drivers and servos.
- Ensure the L298N drivers are pinned according to `Robot_Main.ino`.
- The maze solver sensors operate strictly on pulse-in logic mapped in `MazeSolver.cpp`.

## Using Manual Movement vs Maze Solver
By default, the `loop()` includes commented-out blocks that allow you to toggle between autonomous execution and manual step-by-step movement.

1. Open `Robot_Main/Robot_Main.ino`
2. Scroll to the `loop()` function.
3. If you want manual distance testing, uncomment the `moveForwardCM(10.0);` lines.
4. If you want autonomous maze solving, comment out the manual commands and uncomment `myMazeSolver.solveMaze();`.
