#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
  for (int pin = 2; pin < 6; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }

  pinMode(6, INPUT_PULLUP);

  PCICR |= (1 << PCIE2);   

    PCMSK2 |= (1 << PCINT18) |
              (1 << PCINT19) |
              (1 << PCINT20) |
              (1 << PCINT21) |
              (1 << PCINT22);
}

ISR(PCINT2_vect) {
   if (digitalRead(2) == LOW) 
    { 

    }
    if (digitalRead(3) == LOW) 
      {  

      }
    if (digitalRead(4) == LOW) 
      { 

      }
    if (digitalRead(5) == LOW) 
      { 

      }
    if (digitalRead(6) == LOW) 
    {
      
    }
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
}

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state

*/