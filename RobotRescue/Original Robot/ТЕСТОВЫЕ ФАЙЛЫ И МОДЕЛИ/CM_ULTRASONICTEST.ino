void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(7, LOW);
  delay(5);
  digitalWrite(7, HIGH);
  delay(10);
  digitalWrite(7, LOW);

  int duration = pulseIn(6, HIGH, 15000
  );
  int cmDistation = (duration / 2) / 29.1;

  if (cmDistation > 10){ 
    Serial.println("GO!!!");
  } else {
    Serial.println("Back!!!");
  }

  delay(1000);
}
