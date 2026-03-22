#include "MecanumCar.h"

MecanumCar::MecanumCar(unsigned int fl_en, unsigned int fl_in1, unsigned int fl_in2, 
                       unsigned int fr_en, unsigned int fr_in1, unsigned int fr_in2,
                       unsigned int rl_en, unsigned int rl_in1, unsigned int rl_in2,
                       unsigned int rr_en, unsigned int rr_in1, unsigned int rr_in2) 
{
  motorFL = new L298N(fl_en, fl_in1, fl_in2);
  motorFR = new L298N(fr_en, fr_in1, fr_in2);
  motorRL = new L298N(rl_en, rl_in1, rl_in2);
  motorRR = new L298N(rr_en, rr_in1, rr_in2);
  currentSpeed = 200;
}

MecanumCar::~MecanumCar() {
  delete motorFL; delete motorFR; delete motorRL; delete motorRR;
}

void MecanumCar::setSpeed(int speed) { currentSpeed = speed; }

// This function allows you to update the values
void MecanumCar::setTrim(float fl, float fr, float rl, float rr) {
    trimFL = fl;
    trimFR = fr;
    trimRL = rl;
    trimRR = rr;
}

// This function uses the values to adjust motor power
void MecanumCar::setIndividualSpeeds(int fl, int fr, int rl, int rr) {
    motorFL->setSpeed(fl * trimFL);
    motorFR->setSpeed(fr * trimFR);
    motorRL->setSpeed(rl * trimRL);
    motorRR->setSpeed(rr * trimRR);
}

void MecanumCar::forward() {
  setIndividualSpeeds(currentSpeed, currentSpeed, currentSpeed, currentSpeed);
}

void MecanumCar::backward() {
  setIndividualSpeeds(-currentSpeed, -currentSpeed, -currentSpeed, -currentSpeed);
}

void MecanumCar::turnLeft() {
  setIndividualSpeeds(-currentSpeed, currentSpeed, -currentSpeed, currentSpeed);
}

void MecanumCar::turnRight() {
  setIndividualSpeeds(currentSpeed, -currentSpeed, currentSpeed, -currentSpeed);
}

void MecanumCar::setStrafeSpeed(int speed) {
    strafeSpeed = speed;
}

void MecanumCar::strafeLeft() {
    
    setIndividualSpeeds(-strafeSpeed, strafeSpeed, strafeSpeed, -strafeSpeed);
}

void MecanumCar::strafeRight() {
    setIndividualSpeeds(strafeSpeed, -strafeSpeed, -strafeSpeed, strafeSpeed);
}

void MecanumCar::stop() {
  setIndividualSpeeds(0, 0, 0, 0);
}