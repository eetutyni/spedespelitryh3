#include "display.h"


void initializeDisplay(void)
{

  pinMode(12, OUTPUT); // reset
  pinMode(11, OUTPUT); // shift clock
  pinMode(10, OUTPUT); // latch clock
  pinMode(9, OUTPUT);  // output enable
  pinMode(8, OUTPUT);  // serial data

  digitalWrite(12, HIGH); // vapauta reset
  digitalWrite(9, LOW);   // ulostulot päälle


}
const uint8_t digitTable[] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};


void writeByte(uint8_t bits,bool last)
{

}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
// See requirements for this function from display.h
}

void showResult(byte number)
{
// See requirements for this function from display.h
}

