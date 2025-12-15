#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

// Initialize both 7-segment displays
void initializeDisplay();

// Show a two-digit number (0–99)
void showNumbers(int num);

// Write to left digit (0–9)
void showLeft(int digit);

// Write to right digit (0–9)
void showRight(int digit);

void bitshift(int dataPin, int clockPin, uint8_t value);

// Show score or any result (same as showNumber)
void showResult(int num);

#endif
