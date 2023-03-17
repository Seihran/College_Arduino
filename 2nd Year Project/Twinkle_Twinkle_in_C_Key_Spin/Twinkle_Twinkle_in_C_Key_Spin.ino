#include "pitches.h"

const byte noteA = A0;
const byte noteC = A1;
const byte noteD = A2;
const byte noteE = A3;
const byte noteF = A5;
const byte noteG = A6;
const byte speaker = A7;
const byte noteALED = A8;
const byte noteCLED = A9;
const byte noteDLED = A10;
const byte noteELED = A11;
const byte noteFLED = A12;
const byte noteGLED = A13;

void setup()
{
  pinMode(noteA, INPUT);
  pinMode(noteC, INPUT);
  pinMode(noteD, INPUT);
  pinMode(noteE, INPUT);
  pinMode(noteF, INPUT);
  pinMode(noteG, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(noteALED, OUTPUT);
  pinMode(noteCLED, OUTPUT);
  pinMode(noteDLED, OUTPUT);
  pinMode(noteELED, OUTPUT);
  pinMode(noteFLED, OUTPUT);
  pinMode(noteGLED, OUTPUT);
}

void loop()
{
    float voltageA = analogRead(noteA) * (5.0/1023.0);
    float voltageC = analogRead(noteC) * (5.0/1023.0);
    float voltageD = analogRead(noteD) * (5.0/1023.0);
    float voltageE = analogRead(noteE) * (5.0/1023.0);
    float voltageF = analogRead(noteF) * (5.0/1023.0);
    float voltageG = analogRead(noteG) * (5.0/1023.0);
    digitalWrite(noteALED, HIGH);
    digitalWrite(noteCLED, HIGH);
    digitalWrite(noteDLED, HIGH);
    digitalWrite(noteELED, HIGH);
    digitalWrite(noteFLED, HIGH);
    digitalWrite(noteGLED, HIGH);
    while (voltageA >= 3.0)
      {
        tone(speaker, NOTE_A4);
        voltageA = analogRead(noteA) * (5.0/1023.0);
      }
    while (voltageC >= 3.0)
      {
        tone(speaker, NOTE_C4);
        voltageC = analogRead(noteC) * (5.0/1023.0);
      }
    while (voltageD >= 3.0)
      {
        tone(speaker, NOTE_D4);
        voltageD = analogRead(noteD) * (5.0/1023.0);
      }
    while (voltageE >= 3.0)
      {
        tone(speaker, NOTE_E4);
        voltageE = analogRead(noteE) * (5.0/1023.0);
      }
    while (voltageF >= 3.0)
      {
        tone(speaker, NOTE_F4);
        voltageF = analogRead(noteF) * (5.0/1023.0);
      }
    while (voltageG >= 3.0)
      {
        tone(speaker, NOTE_G4);
        voltageG = analogRead(noteG) * (5.0/1023.0);
      }
    noTone(speaker);
}
