#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2
#define Sensor4 A3
#define Sensor5 A4
#define Sensor6 A5


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(Sensor1));
  Serial.print(' ');
  Serial.print(analogRead(Sensor2));
  Serial.print(' ');
  Serial.print(analogRead(Sensor3));
  Serial.print(' ');
  Serial.print(analogRead(Sensor4));
  Serial.print(' ');
  Serial.print(analogRead(Sensor5));
  Serial.print(' ');
  Serial.print(analogRead(Sensor6));
  Serial.println();
  delay(1000);
}
