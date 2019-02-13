/***
 * For Arduino Mega 2560.
 * This is a work with sensors and Arduino Uno and Raspberry Pi.
 */

#include <SoftwareSerial.h>

SoftwareSerial firstSerial(18, 19);
int ultraSonicPins[][] = {{11, 12}}; // четный номер - trig, нечетный - echo

void setup(){
  Serial.begin(9600);
  firstSerial.begin(9600);

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

int[] readerFromUltrasonics(){
  int echoTemp = 0;
  int trigTemp = 0;
  int valueFromSensors[];
  for (int i = 0; i < ultraSonicPins.length; i++){
    for (int j = 0; j < ultraSonicPins[i].length; j++){
      if (j == 0 || j % 2 == 0 echoTemp = ultraSonicPins[i][j];
      else trigTemp = ultraSonicPins[i][j];
    }

    valueFromSensors[i] = getLengthUltra(trigTemp, echoTemp);
  }

  return valueFromSensors;
}

void loop(){
  if (Serial.available() && firstSerial.available()){
    Serial.println();
  }
}
