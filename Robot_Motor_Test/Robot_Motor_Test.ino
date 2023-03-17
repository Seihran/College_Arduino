#include <ArduinoRobot.h>
#include <Arduino_LCD.h>
#include <Compass.h>
#include <EasyTransfer2.h>
#include <EEPROM_I2C.h>
#include <Fat16.h>
#include <Fat16Config.h>
#include <Fat16mainpage.h>
#include <Fat16util.h>
#include <FatStructs.h>
#include <Multiplexer.h>
#include <SdCard.h>
#include <SdInfo.h>
#include <Squawk.h>
#include <SquawkSD.h>
#include <ArduinoRobotMotorBoard.h>
#include <LineFollow.h>

int speedLeft = 100;
int speedRight = 100;
int degrees = 90;

void setup(){
  RobotMotor.begin();
  } 
  
void loop(){
  Robot.motorsWrite(speedLeft, speedRight);
  delay(1000);
  Robot.motorsStop();
  Robot.turn(degrees);
  Robot.updateIR();
}

void setup()
{
  Robot.begin(); // Start the control board
}

void loop()
{
  // Read in potentiometer values
  int speed = Robot.knobRead();

  //Potentiometer data is 0-1023, motors expect 0-255
  // (we won't use negative values)

  int motorSpeed = map(speed, 0, 1023, 0, 255);

  // Motor variables
  int leftMotor = 0;
  int rightMotor = 0;

  if (Robot.digitalRead(TK5) == true)
    leftMotor = motorSpeed;

  if (Robot.digitalRead(TK7) == true)
    leftMotor = motorSpeed;

  // Now control the motors
  Robot.motorsWrite(leftMotor, rightMotor);

  // Sleep for a tenth of a second
  delay(100);
}
}
