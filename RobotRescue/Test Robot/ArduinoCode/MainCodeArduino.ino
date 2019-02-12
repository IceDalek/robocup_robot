#include <SoftwareSerial.h>

SoftwareSerial firstSerial(18, 19);

void setup(){
  Serial.begin(9600);
  firstSerial.begin(9600);
}

void loop(){
  if (Serial.available() && firstSerial.available()){
    while (Serial.available() && firstSerial.available()){
      for(int i = 0; i < 4; i++){
        firstSerial.write(i);
        Serial.write(firstSerial.read());
      }
    }
  }
}
