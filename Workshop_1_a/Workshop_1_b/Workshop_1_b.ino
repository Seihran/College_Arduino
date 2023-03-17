#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanLEDs.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLCD.h>

#define LDR_LEFT_PORT 6;
#define LDR_RIGHT_PORT 7;

const int buttonA = 9;
const int buttonB = 12;
const int buttonC = 13;
int MinRight = 1000;
int MaxRight = 0;
int MinLeft = 1000;
int MaxLeft = 0;
int LeftLDR;
int RightLDR;

OrangutanMotors motors;
OrangutanLCD lcd;

void setup()
{
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  Serial.begin(9600);
}

void loop()
{
  while (digitalRead(buttonA) == HIGH && digitalRead(buttonB) == HIGH && digitalRead(buttonC) == HIGH)
  {
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print("A->Display");
    lcd.gotoXY(0,1);
    lcd.print("B->Calib");
    delay(100);
  }
  if (digitalRead(buttonA) == LOW)
  {
    delay(1000);
    LDRvalues();
  }
  else if (digitalRead(buttonB) == LOW)
  {
    delay(1000);
    for (int i = 0; i < 100; i++)
    {
    getLeftLDRCalibrated();
    getRightLDRCalibrated();
    delay(100);
    }
  }
  else
  {
    delay(1000);
    moveRobot();
  }
}

void LDRvalues()
{
  lcd.clear();
  while (1)
  {
    int sensorValueL;
    int sensorValueR;
    sensorValueL = analogRead(6);
    sensorValueR = analogRead(7);
    lcd.gotoXY(0,0);
    lcd.print(sensorValueL);
    lcd.gotoXY(0,1);
    lcd.print(sensorValueR);
  }
}

void getLeftLDRCalibrated()
{
  int LDRMinLeft;
  int LDRMaxLeft;
  int sensorValue = analogRead(6);
  
  for (int i = 0; i < 100; i++)
  {
    LDRMinLeft = analogRead(6);
    if (LDRMinLeft < MinLeft)
    {
      MinLeft = LDRMinLeft;
    }
  }
  for (int i = 0; i < 100; i++)
  {
    LDRMaxLeft = analogRead(6);
    if (LDRMaxLeft > MaxLeft)
    {
      MaxLeft = LDRMaxLeft;
    }
  }
  sensorValue = map(sensorValue, MinLeft, MaxLeft, 0, 100);
  lcd.clear();
  lcd.gotoXY(0,0);
  lcd.print(sensorValue);
}

void getRightLDRCalibrated()
{
  int LDRMinRight;
  int LDRMaxRight;
  int sensorValue = analogRead(7);
  
  for (int i = 0; i < 100; i++)
  {
    LDRMinRight = analogRead(7);
    if (LDRMinRight < MinRight)
    {
      MinRight = LDRMinRight;
    }
  }
  for (int i = 0; i < 100; i++)
  {
    LDRMaxRight = analogRead(7);
    if (LDRMaxRight > MaxRight)
    {
      MaxRight = LDRMaxRight;
    }
  }
  sensorValue = map(sensorValue, MinRight, MaxRight, 0, 100);
  lcd.gotoXY(0,1);
  lcd.print(sensorValue);
}

void moveRobot()
{
  int sensorValueL = map(analogRead(6), MinLeft, MaxLeft, 0, 100);
  int sensorValueR = map(analogRead(7), MinRight, MaxRight, 0, 100);
  Serial.println(sensorValueL);
  Serial.println(sensorValueR);
  while (sensorValueL > 10 && sensorValueR > 10)
  {
    if (sensorValueL < (sensorValueR + 10))
    {
      rotateToLeft();
      delay(100);
      sensorValueL = map(analogRead(6), MinLeft, MaxLeft, 0, 100);
      sensorValueR = map(analogRead(7), MinRight, MaxRight, 0, 100);
    }
    else if (sensorValueR < (sensorValueL + 10))
    {
      rotateToRight();
      delay(100);
      sensorValueL = map(analogRead(6), MinLeft, MaxLeft, 0, 100);
      sensorValueR = map(analogRead(7), MinRight, MaxRight, 0, 100);
    }
    else
    {
        goForward();
        delay(100);
        sensorValueL = map(analogRead(6), MinLeft, MaxLeft, 0, 100);
        sensorValueR = map(analogRead(7), MinRight, MaxRight, 0, 100);
    }
  }
    stopRobot();
    delay(10);
}

void rotateToLeft()
{
  motors.setSpeeds(-50, 50);
  delay(100);
}

void rotateToRight()
{
  motors.setSpeeds(50, -50);
  delay(100);
}

void goForward()
{
    motors.setSpeeds(10, 10);
    delay(100);
}

void stopRobot()
{
  motors.setSpeeds(0, 0);
  delay(1000);
}
