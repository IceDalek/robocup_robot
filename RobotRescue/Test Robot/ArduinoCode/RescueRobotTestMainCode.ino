#include <MeMegaPi.h>
#include <Wire.h>

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
int firstMotorSpeed = 100;

// ******** //




// second motor data

const byte NE2 = 38;

const byte interruptPin2 = 19;

MeMegaPiDCMotor secondMotor(PORT2B);

int secondMotorSpeed = 100;

// ******** //

// Line Follower
MeLineFollower lineFinder(PORT_6);

byte stateDriversRobot = STATE_UP; // state of the robot in this moment



// *** MOTORS CONTROL  **** //

void goForward(){

  stateDriversRobot = STATE_UP;

  

  firstMotor.run(firstMotorSpeed);

  secondMotor.run(secondMotorSpeed);

}



void goBack(){

  stateDriversRobot = STATE_BOTTOM;

  

  firstMotor.run(-firstMotorSpeed);

  secondMotor.run(-secondMotorSpeed);

}



void turnRight(){

  stateDriversRobot = STATE_TURN_RIGHT;

  

  firstMotor.run(firstMotorSpeed);
  secondMotor.run(secondMotorSpeed / CONSTANT_DOWN_SPEED);

}



void turnLeft(){

  stateDriversRobot = STATE_TURN_LEFT;

  firstMotor.run(firstMotorSpeed / CONSTANT_DOWN_SPEED);
  secondMotor.run(secondMotorSpeed);

}
// *main method, set settings

void setup(){
  pinMode(NE1, INPUT);
  pinMode(NE2, INPUT);
  Serial.begin(9600);
}



// infinity ...

void loop(){
int lineSensorValue = lineFinder.readSensors();
  
  switch(lineSensorValue){
    case S1_IN_S2_IN: goForward(); Serial.println("GO forward"); break;
    case S1_OUT_S2_IN: turnRight(); Serial.println("Turn right"); break;
    case S1_IN_S2_OUT: turnLeft(); Serial.println("turn left");break;
    case S1_OUT_S2_OUT: goForward();  Serial.println("GO back");break;
    default:break;
  }

  delay(100);
}
