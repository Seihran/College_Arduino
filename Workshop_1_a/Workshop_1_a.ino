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
    delay(1000);
    LDRvalues();
  }
  else if (digitalRead(buttonB) == LOW)
  {
    delay(1000);
    LDRMinMax();
  }
  else
  {
    delay(1000);
  }
}

void LDRvalues()
{
  lcd.clear();
  while (1)
  {
    int LDRLeft;
    int LDRRight;
    LDRLeft = analogRead(6);
    LDRRight = analogRead(7);
    lcd.gotoXY(0,0);
    lcd.print(LDRLeft);
    lcd.gotoXY(0,1);
    lcd.print(LDRRight);
  }
}

void LDRMinMax()
{
  int MinLeft = 1000;
  int MinRight = 1000;
  int MaxLeft = 0;
  int MaxRight = 0;
  int LDRMinLeft;
  int LDRMinRight;
  int LDRMaxLeft;
  int LDRMaxRight;
  
  for (int i = 0; i < 100; i++)
  {
    LDRMinLeft = analogRead(6);
    LDRMinRight = analogRead(7);
    if (LDRMinLeft < MinLeft)
    {
      MinLeft = LDRMinLeft;
    }
    if (LDRMinRight < MinRight)
    {
      MinRight = LDRMinRight;
    }
  }
  for (int i = 0; i < 100; i++)
  {
    LDRMaxLeft = analogRead(6);
    LDRMaxRight = analogRead(7);
    if (LDRMaxLeft > MaxLeft)
    {
      MaxLeft = LDRMaxLeft;
    }
    if (LDRMaxRight > MaxRight)
    {
      MaxRight = LDRMaxRight;
    }
  }
  lcd.clear();
  lcd.gotoXY(0,0);
  lcd.print(MinLeft);
  lcd.gotoXY(6,0);
  lcd.print(MaxLeft);
  lcd.gotoXY(0,1);
  lcd.print(MinRight);
  lcd.gotoXY(6,1);
  lcd.print(MaxRight);
}

int getLeftLDRCalibrated()
{
  
}

int getRightLDRCalibrated()
{
  
}
