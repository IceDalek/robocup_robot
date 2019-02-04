#include <MeMegaPi.h>

/* STATES */
#define STATE_UP 0
#define STATE_BOTTOM 1
#define STATE_TURN_RIGHT 2
#define STATE_TURN_LEFT 3

#define CONSTANT_DOWN_SPEED 2
// ******** //

// first motor data
const byte NE1 = 31;
const byte interruptPin1 = 18;
MeMegaPiDCMotor firstMotor(PORT1B);
int firstMotorSpeed = 50;
// ******** //

// second motor data
const byte NE2 = 38;
const byte interruptPin2 = 19;
MeMegaPiDCMotor secondMotor(PORT2B);
int secondMotorSpeed = 50;
// ******** //

byte stateDriversRobot = STATE_UP; // state of the robot in this moment

// *** MOTORS CONTROL  **** //
void goForward(){
  stateDriverRobot = STATE_UP;
  
  firstMotor.run(firstMotorSpeed);
  secondMotor.run(secondMotorSpeed);
}

void goBack(){
  stateDriverRobot = STATE_BOTTOM;
  
  firstMotor.run(-firstMotorSpeed);
  secondMotor.run(-secondMotorSpeed);
}

void turnRight(){
  stateDriverRobot = STATE_TURN_RIGHT;
  
  firstMotor.run(firstMotorSpeed);
  secondMotor.run(secondMotorSpeed / CONSTANT_DOWN_SPEED);
}

void turnLeft(){
  stateDriverRobot = STATE_TURN_LEFT;
  
  firstMotor.run(firstMotorSpeed / CONSTANT_DOWN_SPEED);
  secondMotor.run(secondMotorSpeed);
}
// ******** //

// *main method, set settings
void setup(){
  pinMode(NE1, INPUT);
  pinMode(NE2, INPUT);
}

// infinity ...
void loop(){
  
}