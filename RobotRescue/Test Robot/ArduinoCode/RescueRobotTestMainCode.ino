#include <MeMegaPi.h>

#include <Wire.h>



/* Состояния робота */

#define STATE_UP 0

#define STATE_TURN_RIGHT 2

#define STATE_TURN_LEFT 3

#define STATE_BOTTOM 4



#define CONSTANT_DOWN_SPEED 2



// ******** //

// Данные первого мотора

const byte NE1 = 31;

const byte interruptPin1 = 18;

MeMegaPiDCMotor firstMotor(PORT1B);

int speedRobot = 255;





// Данные второго мотора

const byte NE2 = 38;

const byte interruptPin2 = 19;

MeMegaPiDCMotor secondMotor(PORT2B);



// Line Follower and Ultrasonic Sensor

MeLineFollower lineFinder(PORT_6);

MeUltrasonicSensor sensorDistation(PORT_7);



byte stateDriversRobot = STATE_UP; // хранение состояния робота



// *** Функции управления положение робота  **** //

void goForward(){

  stateDriversRobot = STATE_UP;



  firstMotor.run(-speedRobot);
  secondMotor.run(+speedRobot);

}



void turnRight(){

  stateDriversRobot = STATE_TURN_RIGHT;
  
  firstMotor.run(+speedRobot);
  secondMotor.run(-speedRobot / CONSTANT_DOWN_SPEED);

}



void turnLeft(){

  stateDriversRobot = STATE_TURN_LEFT;

  firstMotor.run(speedRobot / CONSTANT_DOWN_SPEED);

  secondMotor.run(speedRobot);

}



void goBack(){

  stateDriversRobot = STATE_BOTTOM;



  firstMotor.run(-speedRobot);

  secondMotor.run(-speedRobot);

}

void stopRobot(){
  firstMotor.run(0);
  secondMotor.run(0);
}



// *Функции получения информации с датчиков

int getInformationFromSensorLine(){
  int valueSensorLine = lineFinder.readSensors();
  byte state;



  switch (valueSensorLine){

    case S1_IN_S2_IN: state = STATE_UP; break;

    case S1_OUT_S2_IN: state = STATE_TURN_RIGHT; break;

    default: state = STATE_TURN_LEFT; break;

  }



  if (state == stateDriversRobot) return;



  switch(state){

    case STATE_UP: goForward(); break;

    case STATE_TURN_RIGHT: turnRight(); break;

    case STATE_TURN_LEFT: turnLeft(); break;

    default: break;

  }

}



int getInformationFromUSensor(){

  int value = sensorDistation.distanceCm();

  return value;

}


void controlUltraSonicSensor(){

  int distanceRobot = getInformationFromUSensor();

  if (distanceRobot > 25){
    goForward();
    delay(100);
  } else {
    stopRobot();
    delay(100);
    turnRight();
    delay(100);    
  }

}



void setup(){

  pinMode(NE1, INPUT);
  pinMode(NE2, INPUT);
  Serial.begin(9600);

  goForward();

}



void loop(){
  controlUltraSonicSensor();
  delay(200);
}
