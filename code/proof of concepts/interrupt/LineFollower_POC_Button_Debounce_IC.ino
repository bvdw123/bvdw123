#define ledPin 13
#define interruptPin 2

int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int reading;

#define BOUNCE_TIME 50
static uint32_t lastPressTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {


  
  digitalWrite(ledPin, ledState);


}

unsigned long last = millis();

void blink() {
  
  if (millis()-last > 500)
  {
    ledState = !ledState;
    last = millis();
  }

        

}
