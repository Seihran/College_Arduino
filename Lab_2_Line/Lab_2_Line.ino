#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
unsigned int sensors[5]; 

#include <avr/pgmspace.h>

void setup()
{
  unsigned int counter; 
  
  robot.init(2000);

  OrangutanLCD::clear();
  OrangutanLCD::gotoXY(0,0);
  OrangutanLCD::print("Press B");

  while (!OrangutanPushbuttons::isPressed(BUTTON_B))
  {
    OrangutanLCD::clear();
    OrangutanLCD::gotoXY(0,0);
    OrangutanLCD::print("Get Ready");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::gotoXY(0,0);
    OrangutanLCD::print("Go");
  }

  OrangutanPushbuttons::waitForRelease(BUTTON_B);
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

  OrangutanPushbuttons::waitForRelease(BUTTON_B);
}

void loop()
{
  unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
  
  if (position < 1000)
  {
    OrangutanMotors::setSpeeds(0, 100);
  }
  else if (position < 3000)
  {
    OrangutanMotors::setSpeeds(100, 100);
  }
  else
  {
    OrangutanMotors::setSpeeds(100, 0);
  }
}
