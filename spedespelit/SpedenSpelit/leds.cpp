#include "leds.h"



void initializeLeds() {
pinMode(A2, OUTPUT); //output, jotta ledit syttyy
pinMode(A3, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(A5, OUTPUT);

//ledit sammutettuna aluksi

    clearAllLeds();
}

void setLed(byte ledNumber) {

clearAllLeds();

switch (ledNumber) {
  case 0:
digitalWrite(A2, HIGH);
break;
case 1:
digitalWrite(A3, HIGH);
break;
case 2:
digitalWrite(A4, HIGH);
break;
case 3:
digitalWrite(A5, HIGH);
break;

}
  
}


void clearAllLeds(void) {
digitalWrite(A2, LOW);
digitalWrite(A3, LOW);
digitalWrite(A4, LOW);
digitalWrite(A5, LOW);
} //Sammuttaa ledit

void setAllLeds(void) { //ledit päälle
digitalWrite(A2, HIGH);
digitalWrite(A3, HIGH);
digitalWrite(A4, HIGH);
digitalWrite(A5, HIGH);
}
/*
  show1() subroutine shows numbers 0,1,...,15 as binary numbers
  waits a bit and repeats number "show"
*/
void drawBinary(int number) {
    if (number & 1) digitalWrite(A2, HIGH); else digitalWrite(A2, LOW); // testaa alimmaisen bitin, jos se on 1, ehto on tosi
    if (number & 2) digitalWrite(A3, HIGH); else digitalWrite(A3, LOW);
    if (number & 4) digitalWrite(A4, HIGH); else digitalWrite(A4, LOW);
    if (number & 8) digitalWrite(A5, HIGH); else digitalWrite(A5, LOW);
  }

void show1(void) {
if (!show1Running) {
  show1Running = true;
  lastUpdate = millis();
  showNumber = 0;
}

unsigned long now = millis();

if (now - lastUpdate >= interval) {
  lastUpdate = now; // tarkistaa, onko aika vaihtaa seuraava numero

  
  drawBinary(showNumber);
  showNumber++;

  if (showNumber > 15) {
    showNumber = 0; // kun 15 ylittyy, menee takaisin 0
  }
}
  
}
/*
  show2(int) subroutine shows leds 0,1,2,3,0,1,2,3,.... with increasing
  changing rate. And when top change speed has been reached

    Parameters:
  
  int rounds: This parameter determines how many times 0,1,2,3 sequence
              is shown. 
*/



void show2(int rounds) {
if (!show2Running) {
  show2Running = true;
  roundsLeft = rounds;
  currentLed = 0;
  show2Interval = 300;
  lastChange = millis();
}
unsigned long now = millis();

if (now - lastChange >= show2Interval) {
  lastChange = now;

  
  setLed(currentLed);
  currentLed++;

  if (currentLed >3) {
    currentLed = 0;
    roundsLeft--;
// nopeutetaan joka kierroksella
    if (show2Interval > minInterval) {
      show2Interval -=20;
    }
  }
  if (roundsLeft <= 0) {
    show2Running = false;
    clearAllLeds();
  }
}
}
