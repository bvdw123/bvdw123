//Bij Arduino Uno Serial. Gebruiken
//Bij Arduino Leonardo Serial1. Gebruiken
//!!!!

int state = 0;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  if(Serial1.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial1.read(); // Reads the data from the serial port
 }

 if (state == '0') {
  digitalWrite(13, LOW); // Turn LED OFF
  Serial1.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(13, HIGH);
  Serial1.println("LED: ON");;
  state = 0;
 } 
}


