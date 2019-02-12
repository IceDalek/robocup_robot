#include <Encoder.h>

#define SPEED_FIRST_MOTOR 5
#define DIR_FIRST_MOTOR 4

#define SPEED_SECOND_MOTOR 6
#define DIR_SECOND_MOTOR 7

int speedMotors = 255;

Encoder myEnc(2,3);
long oldPosition = -999;

void stopGoing(int firstSpeedMotor, int secondSpeedMotor){
  analogWrite(firstSpeedMotor, 0);
  analogWrite(secondSpeedMotor, 0);
}

void back(int firstSpeedMotor, int secondSpeedMotor, int dirFirstMotor, int dirSecondMotor){
  digitalWrite(dirFirstMotor, LOW);
  digitalWrite(dirSecondMotor, LOW);
  analogWrite(firstSpeedMotor, speedMotors);
  analogWrite(secondSpeedMotor, speedMotors);
}

void forward(int firstSpeedMotor, int secondSpeedMotor, int dirFirstMotor, int dirSecondMotor){
  analogWrite(firstSpeedMotor, speedMotors);
  analogWrite(secondSpeedMotor, speedMotors);
  digitalWrite(dirFirstMotor, HIGH);
  digitalWrite(dirSecondMotor, HIGH);
}

void turnLeft(int firstSpeedMotor, int secondSpeedMotor, int dirFirstMotor, int dirSecondMotor){
  analogWrite(firstSpeedMotor, speedMotors);
  analogWrite(secondSpeedMotor, speedMotors);
  digitalWrite(dirFirstMotor, HIGH);
  digitalWrite(dirSecondMotor, LOW);
}

void turnRight(int firstSpeedMotor, int secondSpeedMotor, int dirFirstMotor, int dirSecondMotor){
  analogWrite(firstSpeedMotor, speedMotors);
  analogWrite(secondSpeedMotor, speedMotors);
  digitalWrite(dirFirstMotor, LOW);
  digitalWrite(dirSecondMotor, HIGH);
}

void setup(){
  Serial.begin(9600);

  for (int counterMotors = 4; counterMotors < 8; counterMotors++){
    pinMode(counterMotors, OUTPUT);
  }

  forward(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR);
}

void loop(){
  if (Serial.available() > 0){
    int valueForMotors = Serial.read();

    switch (valueForMotors){
      case 0: forward(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); break;
      case 1: back(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); break;
      case 2: turnLeft(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); break;
      case 3: turnRight(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); break;
      case 4: stopGoing(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR); break;
      default: break;
    }
  }
}

