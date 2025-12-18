#include <Arduino.h>
#include "display.h"

// vasen näyttö
const int SRCLK_L = 11;
const int RCLK_L  = 6;
const int SER_L   = 7;

// oikea näyttö
const int SRCLK_R = 8;
const int RCLK_R  = 9;
const int SER_R   = 10;

static const uint8_t digitTable[] =
{
  0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000  // 9
};

void bitshift(int dataPin, int clockPin, uint8_t value)
{
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(dataPin, (value >> i) & 1);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void initializeDisplay()
{
    pinMode(SRCLK_L, OUTPUT);
    pinMode(RCLK_L,  OUTPUT);
    pinMode(SER_L,   OUTPUT);

    pinMode(SRCLK_R, OUTPUT);
    pinMode(RCLK_R,  OUTPUT);
    pinMode(SER_R,   OUTPUT);

    showNumbers(0);
}

void showNumbers(int num)
{
    int left = num / 10;
    int right = num % 10;

    showLeft(left);
    showRight(right);
}

void showLeft(int digit)
{
    digitalWrite(RCLK_L, LOW);
    bitshift(SER_L, SRCLK_L, digitTable[digit]);
    digitalWrite(RCLK_L, HIGH);
}

void showRight(int digit)
{
    digitalWrite(RCLK_R, LOW);
    bitshift(SER_R, SRCLK_R, digitTable[digit]);
    digitalWrite(RCLK_R, HIGH);
}

void showResult(int num)
{
    showNumbers(num);
}
