#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanLEDs.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>

#include <avr/pgmspace.h>
#define LDR_LEFT_PORT 6;
#define LDR_RIGHT_PORT 7;
#define accelerometer 5;

Pololu3pi robot;
unsigned int sensors[5]; 

const int buttonA = 9;
const int buttonB = 12;
const int buttonC = 13;
int Min = 1023;
int Max = 100;
int sensorValueL;
int sensorValueR;
int tiltGround;
unsigned int counter;

OrangutanMotors motors;
OrangutanLCD lcd;

void setup()
{
  pololu_3pi_init_disable_emitter_pin(2000);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
}

void loop()
{
  if (digitalRead(buttonC) == LOW)
  {
    delay(1000);
   // findLight();
    tiltGround = tiltValue();
    lineCalibration();
    delay(1000);
    lineFollow();
    findBalance(tiltGround);
  }
  if (digitalRead(buttonA) == LOW)
  {
    int tilt = tiltValue();
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(tilt);
    motors.setSpeeds(25, 25);
    findBalance(tiltGround);
  }
  if (digitalRead(buttonB) == LOW)
  {
    delay(1000);
    lineCalibration();
    delay(10);
    lineFollow();
  }
}

int getLeftLDR()
{
  sensorValueL = map(analogRead(6), Min, Max, 0, 100);
  return sensorValueL;
}

int getRightLDR()
{
  sensorValueR = map(analogRead(7), Min, Max, 0, 100);
  return sensorValueR;
}

void findLight()
{
  int leftLDR = getLeftLDR();
  int rightLDR = getRightLDR();

  motors.setSpeeds(-50, 50);
    
  while ((leftLDR + rightLDR)/2 < 90)
  {
   leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   if (leftLDR > (rightLDR + 10))
   {
    motors.setSpeeds(-50, 50); 
   }
   else if (rightLDR > (leftLDR + 10))
   {
    motors.setSpeeds(50, -50);
   }
   else
   {
    motors.setSpeeds(50, 50);
   }
  }
  motors.setSpeeds(0, 0);
  delay(100);
  motors.setSpeeds(50, -50);
  delay(640);
}

void lineCalibration()
{
  unsigned int counter;
  
  delay(1000);
  
  for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-40, 40);
      
    robot.calibrateLineSensors(IR_EMITTERS_ON);
    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);
}

void lineFollow()
{ 
  while()
  {
  unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
  if (position < 1000)
  {
    OrangutanMotors::setSpeeds(0, 75);
  }
  else if (position < 3000)
  {
    OrangutanMotors::setSpeeds(75, 75);
  }
  else
  {
    OrangutanMotors::setSpeeds(75, 0);
  }
  }
}

int tiltValue()
{
  int tilt;
  int tiltAv = 0;
  int i;

  for (i = 0; i < 5; i++)
  {
    tilt = analogRead(5);
    tiltAv = tiltAv + tilt;
    delay(1);
  }
  tiltAv = tiltAv/(i+1);
  return tiltAv;
}

void findBalance(int tiltGround)
{
  int tilt = tiltValue();
  int Speed = tilt*3 - tiltGround*3;
  
  while (tilt < tiltGround || tilt > tiltGround)
  {
    if (tilt < (tiltGround - 1))
    {
      motors.setSpeeds(Speed, Speed);
      tilt = tiltValue();
      Speed = tilt*3 - tiltGround*3;
    }
    else if (tilt > (tiltGround + 1))
    {
      motors.setSpeeds(Speed, Speed);
      tilt = tiltValue();
      Speed = tilt*3 - tiltGround*3;
    }
  }
  motors.setSpeeds(0, 0);
}
