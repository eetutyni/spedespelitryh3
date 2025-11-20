#include "leds.h"


1

/*
  initializeLeds() subroutine intializes analog pins A2,A3,A4,A5
  to be used as outputs. Speden Spelit leds are connected to those
  pins.  
*/
void initializeLeds(); {
pinMode(A2, OUTPUT); //output, jotta ledit syttyy
pinMode(A3, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(A5, OUTPUT);

//ledit sammutettuna aluksi

    digitalWrite(A2, LOW); 
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
}
/*
  setLed(byte) sets correct led number given as 0,1,2 or 3
  led number 0 corresponds to led connected at Arduino pin A2
  led number 1 => Arduino pin A3
  led number 2 => Arduino pin A4
  led number 3 => Arduino pin A5
  
  parameters:
  byte ledNumber is 0,1,2 or 3
*/
void setLed(byte ledNumber);{

switch (lednumber) {
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
/*
  clearAllLeds(void) subroutine clears all leds
*/
void clearAllLeds(void); {
digitalWrite(A2, LOW);
digitalWrite(A3, LOW);
digitalWrite(A4, LOW);
digitalWrite(A5, LOW);
} //Sammuttaa ledit
/*
  setAllLeds subroutine sets all leds
*/
void setAllLeds(void); //ledit päälle
digitalWrite(A2, HIGH);
digitalWrite(A3, HIGH);
digitalWrite(A4, HIGH);
digitalWrite(A5, HIGH);
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


unsigned long lastUpdate = 0; 
const unsigned long interval = 200; // 200ms per numero, muuttumaton positiivinen arvo, 
int showNumber = 0;  // 0–15
bool show1Running = false;






void show1(void) {
if (!show1Running) {
  show1Running = true;
  lastUpdate = millis();
  showNumber = 0;
}
unsigned long now = millis();

if (now - lastUpdate >= interval) {
  lastUpdate = now; // tarkistaa, onko aika vaihtaa seuraava numero

  clearAllLeds();
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
void show2(int);

#endif