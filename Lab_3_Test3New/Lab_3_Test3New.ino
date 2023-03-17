// Including all relevant libraries
#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanLEDs.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

// Declaring all global values needed
#include <avr/pgmspace.h>
#define LDR_LEFT_PORT 6;
#define LDR_RIGHT_PORT 7;
#define accelerometer 5;

Pololu3pi robot;

unsigned int sensors[5]; 
const int buttonA = 9;
const int buttonB = 12;
const int buttonC = 13;
int MinL = 937;
int MaxL = 200;
int MinR = 865;
int MaxR = 119;
int sensorValueL;
int sensorValueR;
unsigned int counter;
int tiltGround = 1;
int tilt = 0;
const int filt = 25;
int buffer[filt];
int medBuff[filt];
int count = 0;

OrangutanMotors motors;
OrangutanLCD lcd;
OrangutanBuzzer buzzer;

// Song to play at completion of ramp
const char fugue[] PROGMEM = 
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

void setup()
{
  pololu_3pi_init_disable_emitter_pin(2000);
  // This must be called at the beginning of 3pi code, to set up the
  // sensors.  We use a value of 2000 for the timeout, which
  // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  // Calls the function to establish a baseline tilt value and fills the buffer of the filter
  fillBuff();
}

void loop()
{
  if (digitalRead(buttonA) == LOW)
  {
    // If button A is pressed, complete the line and balance tasks only
    lineCalibration();
    delay(100);
    fillBuff();
    delay(100);
    lineFollow();
    delay(100);
    findBalance();
  }
  if (digitalRead(buttonB) == LOW)
  {
    // If button B is pressed, print to screen the values of the LDR sensors and the accelerometer
    int leftLDR = analogRead(6);
    int rightLDR = analogRead(7);
    int angle = analogRead(5);
    int level = medFilt(tiltGround);
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(leftLDR);
    lcd.gotoXY(5,0);
    lcd.print(rightLDR);
    lcd.gotoXY(0,1);
    lcd.print(angle);
    lcd.gotoXY(5,1);
    lcd.print(level);
    delay(10);
  }
  if (digitalRead(buttonC) == LOW)
  {
    // If button C is pressed, complete all tasks in sequence
    delay(1000);
    findLight();
    delay(100);
    lineCalibration();
    delay(100);
    fillBuff();
    delay(100);
    lineFollow();
    delay(100);
    findBalance();
  }
}

// This function takes the min and max values for the left LDR hardcoded at the beginning and maps them from 0 to 100
int getLeftLDR()
{
  // Maps the values of the left LDR from 0 to 100, where 100 is maximum amount of light
  sensorValueL = map(analogRead(6), MinL, MaxL, 0, 100);
  return sensorValueL;
}

// This function takes the min and max values for the right LDR hardcoded at the beginning and maps them from 0 to 100
int getRightLDR()
{
  // Maps the values of the right LDR from 0 to 100, where 100 is maximum amount of light
  sensorValueR = map(analogRead(7), MinR, MaxR, 0, 100);
  return sensorValueR;
}

// This function rotates until it discovers a light source of sufficient intensity before moving towards it
void findLight()
{
  int leftLDR = getLeftLDR();
  int rightLDR = getRightLDR();
  int LDRValue = (leftLDR + rightLDR)/2;
  // Sums both LDR values and divides them by two to get an average value for the intensity

  // Loop to keep rotating until the intensity is over 6% of the total value of the max the LDRs can sense
  while (LDRValue <= 6)
  {
    motors.setSpeeds(40, -40);
    delay(10);
    leftLDR = getLeftLDR();
    rightLDR = getRightLDR();
    LDRValue = (leftLDR + rightLDR)/2;

    // Stops rotating and breaks the loop when the intensity is
    // at or above 7% of the total value of the max the LDRs can sense
    if (LDRValue >= 7)
    {
      motors.setSpeeds(0, 0);
      delay(1000);
      break;
    }
  }

  // While the intensity average of the LDRs is under 94%, keep rotating and moving towards the light
  while (LDRValue < 94)
  {
   leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   LDRValue = (leftLDR + rightLDR)/2;

   // If the left LDR value is greater than the right LDR + an error value, rotate left
   if (leftLDR > (rightLDR + 8))
   {
    motors.setSpeeds(-50, 50); 
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   LDRValue = (leftLDR + rightLDR)/2;
   }
   // If the right LDR value is greater than the left LDR + an error value, rotate right
   else if (rightLDR > (leftLDR + 10))
   {
    motors.setSpeeds(50, -50);
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   LDRValue = (leftLDR + rightLDR)/2;
   }
   // If both values are similar, move forwards
   else
   {
    motors.setSpeeds(50, 50);
    leftLDR = getLeftLDR();
   rightLDR = getRightLDR();
   LDRValue = (leftLDR + rightLDR)/2;
   }
  }
  // Stop the motors and then rotate 180 degrees
  motors.setSpeeds(0, 0);
  delay(100);
  motors.setSpeeds(50, -50);
  delay(600);
}

// This function records a set of sensor readings and keeps track of the minimum and maximum values encountered
// The IR_EMITTERS_ON argument means that the IR LEDs will be turned on during the reading
void lineCalibration()
{
  unsigned int counter;
  
  for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-35, 35);
      
    robot.calibrateLineSensors(IR_EMITTERS_ON);
    // Since the counter runs to 80, the total delay will be 80*20 = 1600 ms.
    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);
}

// This function takes the calibrated IR readings and uses them to follow a line
// while the accelerometer readings are consistent with the level reading from earlier
void lineFollow()
{ 
  while(medFilt(tiltGround) < 9)
  {
  // Get the position of the line.  Note that we *must* provide the "sensors" argument to read_line() here, even though we
  // are not interested in the individual sensor readings.
  unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);

  // When too far to the right, turn left
  if (position < 1000)
  {
    OrangutanMotors::setSpeeds(10, 65);
  }
  // Else if the IR readings are in the centre, go forwards
  else if (position < 3000)
  {
    OrangutanMotors::setSpeeds(75, 75);
  }
  // Otherwise it is too far to the left, so turn right
  else
  {
    OrangutanMotors::setSpeeds(65, 10);
  }
  }
}

// Takes the input from the accelerometer and fills the buffer of the filter
// Then assigns the accelerometer value to tiltGround
void fillBuff()
{
    for (int i = 0; i < filt; i++)
  {
    buffer[i] = tilt - tiltGround;
    medBuff[i] = tilt - tiltGround;
  }
  tiltGround = analogRead(5);
}

// This function is the moving median filter to allow smoothing of the
// accelerometer data, in case of sudden changes due to sharp turns or sudden stops
int medFilt(int tiltGround)
{
  int tilt;
  boolean check = true;
  int temp, i, j = 0;
  int medBuff[filt] = {};
  
  tilt = analogRead(5) - tiltGround;
  delay(20);

  for (i = 0; i <= filt - 2; i++)
  {
   buffer[i] = buffer[i+1];
  }

  buffer[filt - 1] = tilt;
  
    for (i = 0; i < filt; i++)
    {
      medBuff[i] = buffer[i];
    }

    while (check)
    {
      check = false;
      j++;
      for (i = 0; i < (filt - 1) - j; i++)
      {
        if (medBuff[i] > medBuff[i + 1])
        {
          temp = medBuff[i];
          medBuff[i] = medBuff[i+1];
          medBuff[i+1] = temp;
          check = true;
        }
      }
    }
   return medBuff[filt/2];
}

// This function takes the accelerometer data and uses it to move forwards and backwards
// until the readings indicate that the value is close to the previously established
// ground level
void findBalance()
{
  // Sets a value for speed and error
  int Speed = 28;
  int error = 4;

  // Continuously moves if not at ground level
  while (true)
  {
    // Delay to allow time for new readings to be measured
    delay(200);
    tilt = analogRead(5) - tiltGround;

    // If reading is below the min allowed threshold of ground level, move backwards
    if (tilt < -error)
    {
      motors.setSpeeds(-Speed, -Speed);
      delay(70);
      motors.setSpeeds(0,0);
    }
    // Else if reading is above the max allowed threshold of ground level, move forwards
    else if (tilt > error)
    {
      motors.setSpeeds(Speed, Speed);
      delay(70);
      motors.setSpeeds(0,0);
    }
    // Otherwise stop, as readings are inside threshold values and indicate level ground
    else
    {
      motors.setSpeeds(0, 0);
      // Wait three seconds to ensure robot is properly balanced, then display done
      delay(3000);
      lcd.clear();
      lcd.gotoXY(0,0);
      lcd.print("Done");
      delay(10);
      // Briefly pause after displaying done, then play pre-programmed song for 2 seconds
      buzzer.playFromProgramSpace(fugue);
      delay(2000);
    }
  }
  motors.setSpeeds(0, 0);
}
