#include <Encoder.h>

#define SPEED_1      5 
#define DIR_1        4
 
#define SPEED_2      6
#define DIR_2        7

Encoder myEnc(2,3);
long oldPosition  = -999;

void stopmoving()
{
  analogWrite(SPEED_1, 0);
  analogWrite(SPEED_2, 0);
}
void back()
{
   digitalWrite(DIR_1,LOW);
  analogWrite(SPEED_1, 100);
   digitalWrite(DIR_2,LOW);
  analogWrite(SPEED_2, 100);
}
void forward()
{
   digitalWrite(DIR_1,HIGH);
  analogWrite(SPEED_1, 100);
   digitalWrite(DIR_2,HIGH);
  analogWrite(SPEED_2, 100);
  
}
void right()
{
   digitalWrite(DIR_1,HIGH);
  analogWrite(SPEED_1, 100);
   digitalWrite(DIR_2,LOW);
  analogWrite(SPEED_2, 100);
}
void left()
{
   digitalWrite(DIR_1,LOW);
  analogWrite(SPEED_1, 100);
   digitalWrite(DIR_2,HIGH);
  analogWrite(SPEED_2, 100);
}

void check_encode()
{
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
}
}

void setup() {
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
  
   Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  
} 
 
void loop() {
   check_encode();
   forward();
 //надо понять, что за значение возвращает энкодер и перегрузить функции для движения на определенное расстояние
 //про использование motor shield plus: http://wiki.amperka.ru/продукты:arduino-motor-shield-plus
}
