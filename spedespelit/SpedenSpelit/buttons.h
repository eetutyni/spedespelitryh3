#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


const byte firstGameButtonPin = 2;
const byte lastGameButtonPin  = 5;


// Debounce delay
const unsigned long debounceDelay = 150; // ms

void initButtonsAndButtonInterrupts(void);

ISR(PCINT2_vect);

extern volatile int buttonNumber;  

#endif
