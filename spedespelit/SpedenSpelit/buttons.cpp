#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
  for (int pin = 2; pin < 6; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }
}

ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
}