#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanLEDs.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

#include <avr/pgmspace.h>
#define LDR_LEFT_PORT 6;
#define LDR_RIGHT_PORT 7;
#define accelerometer 5;

Pololu3pi robot;
unsigned int sensors[5]; 

const int buttonA = 9;
const int buttonB = 12;
const int buttonC = 13;
int MinL = 800;
int MaxL = 100;
int MinR = 1023;
int MaxR = 4;
int sensorValueL;
int sensorValueR;
unsigned int counter;
int tiltGround = 1;
int tilt = 0;
const int filt = 25;
int buffer[filt];
int medBuff[filt];
int count = 0;

OrangutanMotors motors;
OrangutanLCD lcd;
OrangutanBuzzer buzzer;

const char fugue[] PROGMEM = 
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

void setup()
{
  pololu_3pi_init_disable_emitter_pin(2000);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  fillBuff();
}

void loop()
{
  if (digitalRead(buttonC) == LOW)
  {
    delay(1000);
    findLight();
    delay(100);
    lineCalibration();
    delay(100);
    fillBuff();
    delay(100);
    lineFollow();
    delay(100);
    findBalance();
  }
  if (digitalRead(buttonA) == LOW)
  {
    lineCalibration();
    delay(100);
    fillBuff();
    delay(100);
    lineFollow();
    delay(100);
    findBalance();
  }
  if (digitalRead(buttonB) == LOW)
  {
    int LeftMax;
    int LeftMin;
    int RightMax;
    int RightMin;
      
    for (int i = 0; i < 50; i++)
    {
      int leftLDR = analogRead(6);
      int rightLDR = analogRead(7);
      lcd.clear();
      lcd.gotoXY(3,0);
      lcd.print(leftLDR);
      lcd.gotoXY(3,1);
      lcd.print(rightLDR);
      delay(10);
      
      if (leftLDR > LeftMax)
      {
        LeftMax = leftLDR;
      }
      else if (leftLDR < LeftMin)
      {
        LeftMin = leftLDR;
      }
      if (rightLDR > RightMax)
      {
        RightMax = rightLDR;
      }
      else if (rightLDR < RightMin)
      {
        RightMin = rightLDR;
      }
    }
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(LeftMax);
    lcd.gotoXY(0,1);
    lcd.print(LeftMin);
    lcd.gotoXY(6,0);
    lcd.print(RightMax);
    lcd.gotoXY(6,1);
    lcd.print(RightMin);
    delay(10);
  }
}

int getLeftLDR()
{
  sensorValueL = map(analogRead(6), MinL, MaxL, 0, 100);
  return sensorValueL;
}

int getRightLDR()
{
  sensorValueR = map(analogRead(7), MinR, MaxR, 0, 100);
  return sensorValueR;
}

void findLight()
{
  int leftLDR = getLeftLDR();
  int rightLDR = getRightLDR();
  int filtValueL = medFilt(leftLDR);
  int filtValueR = medFilt(rightLDR);
  int LDRValue = (leftLDR + rightLDR)/2;
  
  while (LDRValue < 14)
  {
    motors.setSpeeds(40, -40);
    delay(10);
    leftLDR = getLeftLDR();
    rightLDR = getRightLDR();
    filtValueL = medFilt(leftLDR);
    filtValueR = medFilt(rightLDR);
    LDRValue = (leftLDR + rightLDR)/2;
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(0,1);
    lcd.print(rightLDR);
    lcd.gotoXY(6,0);
    lcd.print(leftLDR);
    lcd.gotoXY(6,1);
    lcd.print(leftLDR);
    lcd.gotoXY(0,3);
    lcd.print(LDRValue);
    if (LDRValue >= 20)
    {
      motors.setSpeeds(0, 0);
      delay(1000);
      break;
    }
  }
  
  while (LDRValue < 85)
  {
   leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   filtValueL = medFilt(leftLDR);
   filtValueR = medFilt(rightLDR);
   LDRValue = (leftLDR + rightLDR)/2;
   lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(0,1);
    lcd.print(rightLDR);
    lcd.gotoXY(6,0);
    lcd.print(leftLDR);
    lcd.gotoXY(6,1);
    lcd.print(leftLDR);
    lcd.gotoXY(0,3);
    lcd.print(LDRValue);
   
   if (leftLDR > (rightLDR + 10))
   {
    motors.setSpeeds(-50, 50); 
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   filtValueL = medFilt(leftLDR);
   filtValueR = medFilt(rightLDR);
   LDRValue = (leftLDR + rightLDR)/2;
   lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(0,1);
    lcd.print(rightLDR);
    lcd.gotoXY(6,0);
    lcd.print(leftLDR);
    lcd.gotoXY(6,1);
    lcd.print(leftLDR);
    lcd.gotoXY(0,3);
    lcd.print(LDRValue);
   }
   else if (rightLDR > (leftLDR + 10))
   {
    motors.setSpeeds(50, -50);
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   filtValueL = medFilt(leftLDR);
   filtValueR = medFilt(rightLDR);
   LDRValue = (leftLDR + rightLDR)/2;
   lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(0,1);
    lcd.print(rightLDR);
    lcd.gotoXY(6,0);
    lcd.print(leftLDR);
    lcd.gotoXY(6,1);
    lcd.print(leftLDR);
    lcd.gotoXY(0,3);
    lcd.print(LDRValue);
   }
   else
   {
    motors.setSpeeds(50, 50);
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   filtValueL = medFilt(leftLDR);
   filtValueR = medFilt(rightLDR);
   LDRValue = (leftLDR + rightLDR)/2;
   lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(0,1);
    lcd.print(rightLDR);
    lcd.gotoXY(6,0);
    lcd.print(leftLDR);
    lcd.gotoXY(6,1);
    lcd.print(leftLDR);
    lcd.gotoXY(0,3);
    lcd.print(LDRValue);
   }
  }
  motors.setSpeeds(0, 0);
  delay(100);
  motors.setSpeeds(50, -50);
  delay(600);
}

void lineCalibration()
{
  unsigned int counter;
  
  for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-35, 35);
      
    robot.calibrateLineSensors(IR_EMITTERS_ON);
    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);
}

void lineFollow()
{ 
  while(medFilt(tiltGround) < 9)
  {
  unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
  if (position < 1000)
  {
    OrangutanMotors::setSpeeds(10, 65);
  }
  else if (position < 3000)
  {
    OrangutanMotors::setSpeeds(75, 75);
  }
  else
  {
    OrangutanMotors::setSpeeds(65, 10);
  }
  }
}

void fillBuff()
{
    for (int i = 0; i < filt; i++)
  {
    buffer[i] = tilt - tiltGround;
    medBuff[i] = tilt - tiltGround;
  }
  tiltGround = analogRead(5);
}

int medFilt(int tiltGround)
{
  int tilt;
  boolean check = true;
  int temp, i, j = 0;
  int medBuff[filt] = {};
  
  tilt = analogRead(5) - tiltGround;
  delay(20);

  for (i = 0; i <= filt - 2; i++)
  {
   buffer[i] = buffer[i+1];
  }

  buffer[filt - 1] = tilt;
  
    for (i = 0; i < filt; i++)
    {
      medBuff[i] = buffer[i];
    }

    while (check)
    {
      check = false;
      j++;
      for (i = 0; i < (filt - 1) - j; i++)
      {
        if (medBuff[i] > medBuff[i + 1])
        {
          temp = medBuff[i];
          medBuff[i] = medBuff[i+1];
          medBuff[i+1] = temp;
          check = true;
        }
      }
    }
   return medBuff[filt/2];
}

void findBalance()
{
  int Speed = 28;
  int error = 4;
  
  while (true)
  {
    delay(200);
    tilt = analogRead(5) - tiltGround;
    
    if (tilt < -error)
    {
      motors.setSpeeds(-Speed, -Speed);
      delay(70);
      motors.setSpeeds(0,0);
    }
    else if (tilt > error)
    {
      motors.setSpeeds(Speed, Speed);
      delay(70);
      motors.setSpeeds(0,0);
    }
    else
    {
      motors.setSpeeds(0, 0);
    }
  }
  motors.setSpeeds(0, 0);
  while(true)
  {
    buzzer.playFromProgramSpace(fugue);
  }
}
