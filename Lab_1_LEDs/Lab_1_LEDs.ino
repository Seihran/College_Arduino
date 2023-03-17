#include <OrangutanLEDs.h>

OrangutanLEDs leds; //Initialises "leds" to control of LEDs

void setup()
{
  delay(5000); //Delays by 5 seconds before starting program
}

void loop()
{
  SOS(); //Calls SOS function
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
