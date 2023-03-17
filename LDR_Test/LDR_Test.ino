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
int defaultLeft;
int defaultRight;
int LeftLDRMin;
int LeftLDRMax;
int RightLDRMin;
int RightLDRMax;
int LeftLDR;
int RightLDR;

OrangutanMotors motors;
OrangutanLCD lcd;

void setup()
{
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
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
    int defaultLeft = LDRvalueLeft();
    int defaultRight = LDRvalueRight();
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(defaultLeft);
    lcd.gotoXY(0,1);
    lcd.print(defaultRight);
    delay(10);
  }
  else if (digitalRead(buttonB) == LOW)
  {
    delay(1000);
    CalibrationLeft();
    CalibrationRight();
  }
  else
  {
    delay(1000);
  }
}

int CalibrationLeft()
{
    int LDRValueL = analogRead(6);
    defaultLeft = LDRvalueLeft();
    for (int i = 0; i < 16; i++)
    {
      if (i % 2 == 0)
      {
        motors.setSpeeds(50, -50);
        delay(150);
      }
      else
      {
        motors.setSpeeds(-50, 50);
        delay(300);
      }
      LDRmaxL(defaultLeft);
      LDRminL(defaultLeft);
    }
    int sensorValueL = map(LDRValueL, LeftLDRMin, LeftLDRMax, 0, 100);
    return sensorValueL;
}

int CalibrationRight()
{
    int LDRValueR = analogRead(7);
    defaultRight = LDRvalueRight();
    for (int i = 0; i < 16; i++)
    {
      if (i % 2 == 0)
      {
        motors.setSpeeds(50, -50);
        delay(150);
      }
      else
      {
        motors.setSpeeds(-50, 50);
        delay(300);
      }
      LDRmaxR(defaultRight);
      LDRminR(defaultRight);
    }
    int sensorValueR = map(LDRValueR, RightLDRMin, RightLDRMax, 0, 100);
    return sensorValueR;
}

int LDRvalueLeft()
{
  LeftLDR = analogRead(6);
  defaultLeft = LeftLDR;
  return defaultLeft;
}

int LDRvalueRight()
{
  RightLDR = analogRead(7);
  defaultRight = RightLDR;
  return defaultRight;
}

int LDRmaxL(int defaultLeft)
{
  for (int i = 0; i < 10; i++)
  {
    LeftLDR = analogRead(6);
    if (LeftLDR > defaultLeft)
    {
      defaultLeft = LeftLDR;
    }
  }
  int LeftLDRMax = LeftLDR;
  return LeftLDRMax;
}

int LDRmaxR(int defaultRight)
{
  for (int i = 0; i < 10; i++)
  {
    RightLDR = analogRead(7);
    if (RightLDR > defaultRight)
    {
      defaultRight = RightLDR;
    }
  }
  int RightLDRMax = RightLDR;
  return RightLDRMax;
}

int LDRminL(int defaultLeft)
{
  for (int i = 0; i < 10; i++)
  {
    LeftLDR = analogRead(6);
    if (LeftLDR < defaultLeft)
    {
      defaultLeft = LeftLDR;
    }
  }
  int LeftLDRMin = LeftLDR;
  return LeftLDRMin;
}

int LDRminR(int defaultRight)
{
  for (int i = 0; i < 10; i++)
  {
    RightLDR = analogRead(7);
    if (RightLDR < defaultRight)
    {
      defaultRight = RightLDR;
    }
  }
  int RightLDRMin = RightLDR;
  return RightLDRMin;
}
