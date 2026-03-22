#pragma once
#include <Arduino.h>
#include <MDLib.h> 

class MecanumCar {
  private:
    L298N* motorFL; 
    L298N* motorFR;
    L298N* motorRL; 
    L298N* motorRR;
    int strafeSpeed;
    int currentSpeed;
    float forwardSpeedCmPerSec;
    
    float turnSpeedDegreesPerSec;
    // CHANGE THESE NAMES TO MATCH YOUR .CPP FILE:
    float trimFL = 1.0; 
    float trimFR = 1.0; 
    float trimRL = 1.0; 
    float trimRR = 1.0;

  public:
    MecanumCar(unsigned int fl_en, unsigned int fl_in1, unsigned int fl_in2, 
               unsigned int fr_en, unsigned int fr_in1, unsigned int fr_in2,
               unsigned int rl_en, unsigned int rl_in1, unsigned int rl_in2,
               unsigned int rr_en, unsigned int rr_in1, unsigned int rr_in2);
    ~MecanumCar();

    void setStrafeSpeed(int speed);
    void setTrim(float fl, float fr, float rl, float rr);
    void setSpeed(int speed);
    void setIndividualSpeeds(int fl, int fr, int rl, int rr); 
    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void strafeLeft(); 
    void strafeRight();
    void stop();
};