#include <NewPing.h>
#include <Thread.h>

NewPing eyes1(2, 3, 40); // first - TRIG, second - ECHO, third - MAX DISTANTION
NewPing eyes2(4, 5, 40);
NewPing eyes3(7, 6, 40);
Thread eyes1_t = Thread(); // первый поток для первого УЗ-датчика
Thread eyes2_t = Thread(); // второй поток для второго УЗ-датчика
Thread eyes3_t = Thread(); // третий поток для третьего УЗ-датчика

void setup() {
  Serial.begin(9600);

  eyes1_t.onRun(getInfoSensor1); // назначаем функцию в поток
  eyes1_t.setInterval(1000); // ставим интервал выполнения

  eyes2_t.onRun(getInfoSensor2);
  eyes2_t.setInterval(1000);

  eyes3_t.onRun(getInfoSensor3);
  eyes3_t.setInterval(1000);
}

void loop() {
  if (eyes1_t.shouldRun()){ // пришло время переключиться
    eyes1_t.run(); // запускаем поток
  }
  if (eyes2_t.shouldRun()){
    eyes2_t.run();
  }
  if (eyes3_t.shouldRun()){
    eyes3_t.run();
  }
}

void getInfoSensor1(){
  Serial.println("eyes1:" + String(eyes1.ping_cm())); // выводим информацию в консоль смп
}
void getInfoSensor2(){
  Serial.println("eyes2:" + String(eyes2.ping_cm()));
}
void getInfoSensor3(){
  Serial.println("eyes3:" + String(eyes3.ping_cm()));
}
