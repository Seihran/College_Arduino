#include <OrangutanMotors.h>

OrangutanMotors motors; //Initialises motors to control motors

void setup()
{
  delay(5000); //Delays for five seconds on startup
}

void loop()
{
  Square(); //Calls Square function
}

void Square() //Creates a for loop to move robot in square pattern
{
  for (int i = 0; i < 4; i++)
  {
    motors.setSpeeds(100, 100); //Moves robot forward for 1/3 of a second
    delay(300);
    motors.setSpeeds(50, -50); //Turns robot 90 deg to the right
    delay(290);
  }
}
