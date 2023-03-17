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
void setup() {
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
void loop() {
  float voltageA = analogRead(noteA) * (5.0 / 1023.0);
  float voltageC = analogRead(noteC) * (5.0 / 1023.0);
  float voltageD = analogRead(noteD) * (5.0 / 1023.0);
  float voltageE = analogRead(noteE) * (5.0 / 1023.0);
  float voltageF = analogRead(noteF) * (5.0 / 1023.0);
  float voltageG = analogRead(noteG) * (5.0 / 1023.0);
  digitalWrite(noteALED, HIGH);
  digitalWrite(noteCLED, HIGH);
  digitalWrite(noteDLED, HIGH);
  digitalWrite(noteELED, HIGH);
  digitalWrite(noteFLED, HIGH);
  digitalWrite(noteGLED, HIGH);
  while (voltageA >= 3.0) {
    tone(speaker, NOTE_A4);
    voltageA = analogRead(noteA) * (5.0 / 1023.0);
  }
  while (voltageC >= 3.0) {
    tone(speaker, NOTE_C4);
    voltageC = analogRead(noteC) * (5.0 / 1023.0);
  }
  while (voltageD >= 3.0) {
    tone(speaker, NOTE_D4);
    voltageD = analogRead(noteD) * (5.0 / 1023.0);
  }
  while (voltageE >= 3.0) {
    tone(speaker, NOTE_E4);
    voltageE = analogRead(noteE) * (5.0 / 1023.0);
  }
  while (voltageF >= 3.0) {
    tone(speaker, NOTE_F4);
    voltageF = analogRead(noteF) * (5.0 / 1023.0);
  }
  while (voltageG >= 3.0) {
    tone(speaker, NOTE_G4);
    voltageG = analogRead(noteG) * (5.0 / 1023.0);
  }
  noTone(speaker);
}
Final Design :
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
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
  NOTE_D4, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};
int melody2[] = {
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4
};
const int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2
};
const int noteDurations2[] = {
  3, 8, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 3, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1
};
void setup() {
  Serial.begin(9600);
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
  int noteDuration;
  int pauseBetweenNotes;
  int i = 0;
  while (i < 42) {
    delay(50);
    float voltageA = analogRead(noteA) * (5.0 / 1023.0);
    float voltageC = analogRead(noteC) * (5.0 / 1023.0);
    float voltageD = analogRead(noteD) * (5.0 / 1023.0);
    float voltageE = analogRead(noteE) * (5.0 / 1023.0);
    float voltageF = analogRead(noteF) * (5.0 / 1023.0);
    float voltageG = analogRead(noteG) * (5.0 / 1023.0);
    Serial.println(voltageA);
    Serial.println(voltageC);
    Serial.println(voltageD);
    Serial.println(voltageE);
    Serial.println(voltageF);
    Serial.println(voltageG);
    if (melody[i] == NOTE_A4) {
      digitalWrite(noteALED, HIGH);
    } else if (melody[i] == NOTE_C4) {
      digitalWrite(noteCLED, HIGH);
    } else if (melody[i] == NOTE_D4) {
      digitalWrite(noteDLED, HIGH);
    } else if (melody[i] == NOTE_E4) {
      digitalWrite(noteELED, HIGH);
    } else if (melody[i] == NOTE_F4) {
      digitalWrite(noteFLED, HIGH);
    } else if (melody[i] == NOTE_G4) {
      digitalWrite(noteGLED, HIGH);
    }
    delay(10);
    if (voltageA >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_A4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteALED, LOW);
      i++;
    } else if (voltageC >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_C4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteCLED, LOW);
      i++;
    } else if (voltageD >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_D4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteDLED, LOW);
      i++;
    } else if (voltageE >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_E4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteELED, LOW);
      i++;
    } else if (voltageF >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_F4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteFLED, LOW);
      i++;
    } else if (voltageG >= 3.0) {
      noteDuration = 1000 / noteDurations[i];
      tone(speaker, NOTE_G4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteGLED, LOW);
      i++;
    }
  }
  i = 0;
  while (i < 42) {
    delay(50);
    float voltageA = analogRead(noteA) * (5.0 / 1023.0);
    float voltageC = analogRead(noteC) * (5.0 / 1023.0);
    float voltageD = analogRead(noteD) * (5.0 / 1023.0);
    float voltageE = analogRead(noteE) * (5.0 / 1023.0);
    float voltageF = analogRead(noteF) * (5.0 / 1023.0);
    float voltageG = analogRead(noteG) * (5.0 / 1023.0);
    Serial.println(voltageA);
    Serial.println(voltageC);
    Serial.println(voltageD);
    Serial.println(voltageE);
    Serial.println(voltageF);
    Serial.println(voltageG);
    if (melody2[i] == NOTE_A4) {
      digitalWrite(noteALED, HIGH);
    } else if (melody2[i] == NOTE_C4) {
      digitalWrite(noteCLED, HIGH);
    } else if (melody2[i] == NOTE_D4) {
      digitalWrite(noteDLED, HIGH);
    } else if (melody2[i] == NOTE_E4) {
      digitalWrite(noteELED, HIGH);
    } else if (melody2[i] == NOTE_F4) {
      digitalWrite(noteFLED, HIGH);
    } else if (melody2[i] == NOTE_G4) {
      digitalWrite(noteGLED, HIGH);
    }
    delay(10);
    if (voltageA >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_A4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteALED, LOW);
      i++;
    } else if (voltageC >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_C4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteCLED, LOW);
      i++;
    } else if (voltageD >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_D4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteDLED, LOW);
      i++;
    } else if (voltageE >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_E4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteELED, LOW);
      i++;
    } else if (voltageF >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_F4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteFLED, LOW);
      i++;
    } else if (voltageG >= 3.0) {
      noteDuration = 1000 / noteDurations2[i];
      tone(speaker, NOTE_G4, noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(speaker);
      digitalWrite(noteGLED, LOW);
      i++;
    }
  }
}
void loop() {}