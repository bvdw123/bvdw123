#define AIN1 5
#define AIN2 6
#define BIN1 9
#define BIN2 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);

  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);

  for (int i = 0; i <= 255; i++) {

    analogWrite(AIN1, i);
    delay(10);
  }

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);

  for (int i = 0; i <= 255; i++) {

    analogWrite(BIN1, i);
    delay(10);
  }

  delay(1000);

  for (int i = 255; i >= 0; i--) {

    analogWrite(AIN1, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {

    analogWrite(BIN1, i);
    delay(10);
  }


  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);

  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);

  for (int i = 0; i <= 255; i++) {

    analogWrite(AIN2, i);
    delay(10);
  }

  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);

  for (int i = 0; i <= 255; i++) {

    analogWrite(BIN2, i);
    delay(10);
  }

  delay(1000);

  for (int i = 255; i >= 0; i--) {

    analogWrite(AIN2, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {

    analogWrite(BIN2, i);
    delay(10);
  }

  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);

  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);

  for (int i = 0; i <= 255; i++) {

    analogWrite(BIN2, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {

    analogWrite(AIN1, i);
    delay(10);
  }

  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);

  delay(1000);


}
