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
int MinRight = 1023;
int MaxRight = 100;
int MinLeft = 1023;
int MaxLeft = 100;
int sensorValueL;
int sensorValueR;

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
    lcd.print("Display");
  }
  if (digitalRead(buttonC) == LOW)
  {
    delay(1000);
    findLight();
  }
}

int getLeftLDR()
{
  sensorValueL = map(analogRead(6), MinLeft, MaxLeft, 0, 100);
  return sensorValueL;
}

int getRightLDR()
{
  sensorValueR = map(analogRead(7), MinRight, MaxRight, 0, 100);
  return sensorValueR;
}

void findLight()
{
  int leftLDR = getLeftLDR();;
  int rightLDR = getRightLDR();

  lcd.clear();
  lcd.gotoXY(0,0);
  lcd.print(leftLDR);
  lcd.clear();
  lcd.gotoXY(0,1);
  lcd.print(rightLDR);
  
  if ((leftLDR + rightLDR)/2 < 5)
  {
    motors.setSpeeds(-100, 100);
    delay(300);
  }
  else
  {
    while ((leftLDR + rightLDR)/2 < 90)
    {
     leftLDR = getLeftLDR();
     rightLDR = getRightLDR();
     if (leftLDR > (rightLDR + 10))
     {
      motors.setSpeeds(-50, 50); 
      delay(10);
     }
     else if (rightLDR > (leftLDR + 10))
     {
      motors.setSpeeds(50, -50);
      delay(10);
     }
     else
     {
      motors.setSpeeds(50, 50);
      delay(100);
     }
    }
  }
  motors.setSpeeds(0, 0);
  delay(1000);
}
