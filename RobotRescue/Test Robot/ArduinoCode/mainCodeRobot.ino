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
int speedRobot = 100;


// Данные второго мотора
const byte NE2 = 38;
const byte interruptPin2 = 19;
MeMegaPiDCMotor secondMotor(PORT2B);

// Line Follower and Ultrasonic Sensor
MeLineFollower lineFinder(PORT_6);
MeUltrasonicSensor sensorDistation(PORT_8);

byte stateDriversRobot = STATE_UP; // хранение состояния робота

// *** Функции управления положение робота  **** //
void goForward(){
  stateDriversRobot = STATE_UP;

  firstMotor.run(firstMotorSpeed);
  secondMotor.run(secondMotorSpeed);
}

void turnRight(){
  stateDriversRobot = STATE_TURN_RIGHT;

  firstMotor.run(speedRobot);
  secondMotor.run(speedRobot / CONSTANT_DOWN_SPEED);
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

// *Функции получения информации с датчиков
int getInformationFromSensorLine(){
  int value = lineFinder.readSensors();
  return value;
}

int getInformationFromUSensor(){
  int value = sensorDistation();
  return value;
}

// **** ФУНКЦИИ УПРАВЛЕНИЯ СОСТОЯНИЕМ РОБОТА ***** //
void beginReadLine(){
  int getValueSensorLine = getInformationFromSensorLine();
  switchStateRobot(getValueSensorLine);
}

void changeStateOfRobot(int valueSensorLine){
  byte state;

  switch (valueSensorLine){
    case S1_IN_S2_IN: state = STATE_UP; break;
    case S1_OUT_S2_IN: state = STATE_TURN_RIGHT; break;
    default: state = TURN_LEFT; break;
  }

  if (state == stateDriversRobot) return;

  switch(state){
    case STATE_UP: goForward(); break;
    case STATE_TURN_RIGHT: turnRight(); break;
    case STATE_TURN_LEFT: turnLeft(); break;
    default: break;
  }
}

void controlUltraSonicSensor(){
  int distanceRobot = getInformationFromUSensor();

  if (distanceRobot < 25){
    goBack();
  }
}

void setup(){
  pinMode(NE1, INPUT);
  pinMode(NE2, INPUT);
  Serial.begin(9600);

  goForward();
}

void loop(){
  beginReadLine();
  delay(200);
}
