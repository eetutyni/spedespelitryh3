// leds.h
#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

extern int currentLed;
extern bool show2Running;
extern unsigned long show2Interval;
extern unsigned long lastChange;
extern int roundsLeft;

extern int showNumber;
extern bool show1Running;
extern unsigned long lastUpdate;
extern const unsigned long interval;
extern const unsigned long minInterval;

void initializeLeds();
void setLed(byte ledNumber);
void clearAllLeds();
void setAllLeds();
void drawBinary(int number);
void show1();
void show2(int rounds);

#endif
