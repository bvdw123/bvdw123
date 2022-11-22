// Empty met kalibratie toegevoegd 17/11/2022

#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial1
#define Baudrate 115200

#define AIN1 13
#define AIN2 11
#define BIN1 10
#define BIN2 9

#define interruptPin 2

SerialCommand sCmd(SerialPort);
bool debug;

unsigned long previous, calculationTime;


const int sensor[] = {A0, A1, A2, A3, A4, A5};

long normalised[6];
float debugPosition;

struct param_t
{
  /* andere parameters die in het eeprom geheugen moeten opgeslagen worden voeg je hier toe ... */
  unsigned long cycleTime;
  int black[6];
  int white[6];
  uint16_t power;
  float diff;
  float kp;
  bool run;

} params;


void setup()
{
  SerialPort.begin(Baudrate);

  sCmd.addCommand("stop", onStop);
  sCmd.addCommand("start", onStart);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), button, RISING);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  params.run = false;

  SerialPort.println("ready");
}

void loop()
{
  sCmd.readSerial();
 
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;

    /* code die cyclisch moet uitgevoerd worden programmeer je hier ... */

    



    /* normaliseren en interpoleren sensor */

    for (int i = 0; i < 6; i++)
    {
      
      normalised[i]= map(analogRead(sensor[i]),params.black[i], params.white[i], 0, 1000);
      //SerialPort.print(normalised[i]);
      //SerialPort.print(" ");
    }
    //SerialPort.println();

    //Meest zwarte waarde bepalen
    float position;
    int index = 0;
    for (int i = 1; i < 6; i++) if (normalised[i] < normalised[index]) index = i;
    
    //als er geen lijn meer is stoppen
    if (normalised[index] > 950) params.run = false;

    //Positie bepalen

    if (index == 0) position = -30;

    else if (index == 5) position = 30;

    else {

      int sNul = normalised[index];
      int sMinEen = normalised[index-1];
      int sPlusEen = normalised[index+1];

      float b = sPlusEen - sMinEen;
      b = b / 2;

      float a = sPlusEen - b - sNul;

      position = -b / (2 * a);

      position += index;
      position -= 2.5;

      position *=15;

    }

    debugPosition = position;

    /* pid regeling */

    //proportioneel regelen

    float error = -position;
    float output = error * params.kp;

    output = constrain(output, -510, 510); //output begrenzen voor pwm waardes

    int powerLeft = 0;
    int powerRight = 0;


    if (params.run) if (output >= 0)
    { 
      powerLeft = constrain(params.power + params.diff * output, -255, 255);
      powerRight = constrain(powerLeft - output, -255, 255);
      powerLeft = powerRight + output;
    }

    else
    {   
      powerRight = constrain(params.power - params.diff * output, -255, 255);
      powerLeft = constrain(powerRight + output, -255, 255);
      powerRight = powerLeft - output;
    }

    /* aansturen motoren */

    analogWrite(AIN1, powerLeft > 0 ? powerLeft : 0);
    analogWrite(AIN2, powerLeft < 0 ? -powerLeft : 0);
    analogWrite(BIN1, powerRight > 0 ? powerRight : 0);
    analogWrite(BIN2, powerRight < 0 ? -powerRight : 0);

  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();  
  
  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);

  /* parameters een nieuwe waarde geven via het set commando doe je hier ... */
  
  EEPROM_writeAnything(0, params);
}

void onDebug()
{
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);
  
  /* parameters weergeven met behulp van het debug commando doe je hier ... */

  SerialPort.print("black: ");
  for (int i = 0; i < 6; i++)
  {
    SerialPort.print(params.black[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("white: ");
  for (int i = 0; i < 6; i++)
  {
    SerialPort.print(params.white[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("normalised: ");
  for (int i = 0; i < 6; i++) {
    SerialPort.print(normalised[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("position: ");
  SerialPort.println(debugPosition);

  SerialPort.print("power: ");
  SerialPort.println(params.power);
  SerialPort.print("diff: ");
  SerialPort.println(params.diff);
  SerialPort.print("kp: ");
  SerialPort.println(params.kp);
  SerialPort.print("running: ");
  SerialPort.println(params.run);


  
  SerialPort.print("calculation time: ");
  SerialPort.println(calculationTime);
  calculationTime = 0;
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("done");      
  }
  //naar geheugen schrijven
  EEPROM_writeAnything(0, params);
}

void onStop()
{
  params.run = false;
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);

}

void onStart()
{
 params.run = true;
}

unsigned long last = millis();

void button()
{
  if (millis() - last > 500)
  {
    params.run = !params.run;
    last = millis();
  }
}
