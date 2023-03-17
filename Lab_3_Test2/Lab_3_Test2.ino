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
int tilt = analogRead(5);
const int filter_size = 10;
int buffer[filter_size];
int count = 0;
  int leftLDR = getLeftLDR();
  int rightLDR = getRightLDR();
  int LDRValue = (leftLDR + rightLDR)/2;

OrangutanMotors motors;
OrangutanLCD lcd;

void setup()
{
  pololu_3pi_init_disable_emitter_pin(2000);

}


void loop() {
  // put your main code here, to run repeatedly:
   while (LDRValue < 21)
  {
    motors.setSpeeds(40, -40);
    delay(300);
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(LDRValue);
    delay(10);
    leftLDR = getLeftLDR();
    rightLDR = getRightLDR();
    LDRValue = (leftLDR + rightLDR)/2;
    if (LDRValue > 21)
    {
      break;
    }
  }
  delay(5000);
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
