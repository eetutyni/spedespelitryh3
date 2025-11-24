#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;         
volatile bool newTimerInterrupt = false;  
static int interruptCount = 0;
int currentLed = -1;
bool correct = false;
bool running = false;


void setup()
{
  initButtonsAndButtonInterrupts();
  /*
    Initialize here all modules
  */
}

void loop()
{
  if(buttonNumber>=0)
  {
 if (startRequested) {
    startRequested = false;
    startNewGame();
  }

  if (buttonNumber != -1) {
    checkPlayerInput(buttonNumber);
    buttonNumber = -1;
  }
}
     // start the game if buttonNumber == 6
     // check the game if 0<=buttonNumber<6
  }

  if(newTimerInterrupt == true)
  {

     // new random number must be generated
     // and corresponding let must be activated
  }
}

void resetGame()
{

}

void initializeTimer(void)
{
  cli();
  TCCR1A = 0;
  TCCR1B = (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  OCR1A = 15624;
  TIMSK1 |= (1 << OCIE1A);

	// see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
    newTimerInterrupt = true;

    interruptCount++;

    if(interruptCount >= 10)
    {
      OCR1A = OCR1A / 2;

      interruptCount = 0;
    }
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	currentLed = -1;
  interruptCount = 0;
  newTimerInterrupt = false;  
  int currentLed = -1;
  correct = false;
  buttonNumber = -1;    
  running = true;
}

void startTheGame()
{
  initializeGame();
  initializeTimer();
  
   // see requirements for the function from SpedenSpelit.h
}
