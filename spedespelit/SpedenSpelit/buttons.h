#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Button pins
const byte firstGameButtonPin = 2;
const byte lastGameButtonPin  = 5;
const byte startButtonPin     = 6;

// Debounce delay
const unsigned long debounceDelay = 50; // ms

// Initialize buttons and pin-change interrupts
void initButtonsAndButtonInterrupts(void);

// ISR declaration
ISR(PCINT2_vect);

// Shared with loop()
extern volatile int buttonNumber;   // 1–4 = game buttons, 5 = start button

#endif
