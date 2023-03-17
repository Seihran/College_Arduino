#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanLEDs.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

#define LDR_LEFT_PORT 6;
#define LDR_RIGHT_PORT 7;

Pololu3pi robot;

const int buttonB = 12;

OrangutanLCD lcd;

void setup()
{
  pololu_3pi_init_disable_emitter_pin(2000);
  pinMode(buttonB, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(buttonB) == LOW)
  {
    int LeftMax =0;
    int LeftMin =1023;
    int RightMax =0;
    int RightMin =1023;
      
    for (int i = 0; i < 500; i++)
    {
      int leftLDR = analogRead(6);
      int rightLDR = analogRead(7);
      lcd.clear();
      lcd.gotoXY(3,0);
      lcd.print(leftLDR);
      lcd.gotoXY(3,1);
      lcd.print(rightLDR);
      delay(10);

      if (rightLDR > RightMax)
      {
        RightMax = rightLDR;
      }
      else if (rightLDR < RightMin)
      {
        RightMin = rightLDR;
      }
      if (leftLDR > LeftMax)
      {
        LeftMax = leftLDR;
      }
      else if (leftLDR < LeftMin)
      {
        LeftMin = leftLDR;
      }
    }
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(LeftMax);
    lcd.gotoXY(0,1);
    lcd.print(LeftMin);
    lcd.gotoXY(5,0);
    lcd.print(RightMax);
    lcd.gotoXY(5,1);
    lcd.print(RightMin);
    delay(10);
  }
}
