#include <OrangutanMotors.h>
#include <OrangutanLEDs.h>

OrangutanMotors motors; //Initialises motors to control motors
OrangutanLEDs leds; //Initialises "leds" to control of LEDs

void setup()
{
  delay(5000); //Delays for five seconds on startup
}

void loop()
{
  Square(); //Calls Square function
  SOS(); //Calls SOS function
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

void SOS() //Function to call dot and dash functions into SOS order
{
  dot();
  dash();
  dot();
  
  delay(3000);
}

void dot() //Blinks LED for half second to symbolise dot
{
   for (int i = 0; i < 3; i++)
  {
    leds.red(HIGH);
    delay(500);
    leds.red(LOW);
    delay(500);
  }
}

void dash() //Blinks LED for one second to symbolise dash
{
  for (int i = 0; i < 3; i++)
  {
    leds.red(HIGH);
    delay(1000);
    leds.red(LOW);
    delay(500);
  }
}
