#include <Encoder.h>
#include <SoftwareSerial.h>

#define SPEED_FIRST_MOTOR 5
#define DIR_FIRST_MOTOR 4

#define SPEED_SECOND_MOTOR 6
#define DIR_SECOND_MOTOR 7

int speedMotors = 255;
Encoder myEncoder(2,3);
long oldPosition = -999;

int ultraSonicPins[][] = {{11, 12}}; // четный номер - trig, нечетный - echo

SoftwareSerial firstSerial(0, 1);

void stopGoing(int firstSpeedMotor, int secondSpeedMotor, int dir_pin_first, int dir_pin_second){
  analogWrite(firstSpeedMotor, 0);
  analogWrite(secondSpeedMotor, 0);
  digitalWrite(dir_pin_first, LOW);
  digitalWrite(dir_pin_second, LOW);
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
  firstSerial.begin(9600);

  for (int counterMotors = 4; counterMotors < 8; counterMotors++){
    pinMode(counterMotors, OUTPUT);
  }

  forward(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR);


  // инициалиация пинов дальномеров
  for (int i = 0; i < ultraSonicPins.length; i++){
    for (int j = 0; j < ultraSonicPin[i].length; j++){
      if (j == 0 || j % 2 != 0)
        pinMode(ultraSonicPin[i][j], INPUT);
      else pinMode(ultraSonicPin[i][j], OUTPUT);
    }
  }
}

int getLengthUltra(int pinEcho, int pinTrig){
  unsigned int distationInfo = 0;
  unsigned int signalInfo = 0;

  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  signalInfo = pulseIn(pinEcho, HIGH);
  distation = signalInfo / 58;

  delay(100);

  return distation;
} 

int readerFromUltrasonics(){
  
}

void loop(){
  if (Serial.available()){
    while (firstSerial.available()){
      int valueForMotors = firstSerial.read();
      firstSerial.println(valueForMotors);
      switch (valueForMotors){
        case 0: forward(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); 
                Serial.println("FORWARD");
        break;
        case 1: back(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR);
                Serial.println("BACK");
        break;
        case 2: turnLeft(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR);
                Serial.println("TURN LEFT");
        case 3: turnRight(SPEED_FIRST_MOTOR, SPEED_SECOND_MOTOR, DIR_FIRST_MOTOR, DIR_SECOND_MOTOR); 
                Serial.println("TURN RIGHT");
        break;
        default: Serial.println("Stop going..."); 
                 stopGoing(DIR_FIRST_MOTOR, DIR_SECOND_MOTOR);
        break;
      }
    }
    
    delay(1000);
  }
}

