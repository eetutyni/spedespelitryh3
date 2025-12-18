#include "leds.h"
#include "buttons.h"
#include <Arduino.h>
#include "display.h"
#include "melody.h"   

volatile int buttonNumber = -1;
int score = 0;
volatile bool newTimerInterrupt = false;

int currentLed = -1;
int previousLed = -1;
bool running = false;
bool idle = true;
unsigned long startMillis = 0;
static int interruptCount = 0;

// Timer1 initialization
void initializeTimer(void)
{
    cli();
    TCCR1A = 0;
    TCCR1B = (1 << WGM12); // CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
    OCR1A = 15624; // 1Hz approx
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    newTimerInterrupt = true;
    interruptCount++;
    if (interruptCount >= 10)
{
    if (OCR1A > 800)        // minimum speed
    {
        OCR1A = OCR1A * 0.85;  //nopeutus, about 15% nopeampi per 10 keskeytystä
    }
    interruptCount = 0;
}


}

void showNextLed()
{
    previousLed = currentLed;  
    
    currentLed = random(0,4);

    clearAllLeds();
    setLed(currentLed);
}

void checkGame(byte nbrOfButtonPush)
{
     // jos napin numero on sama kuin ledin numro = oikein, jos ei niin väärin, tarkistaa myös edellisen ledin eli voi painaa edellistä ja sitten nykyistä.
    if (nbrOfButtonPush == currentLed + 1)
    {
        score++;
        showResult(score);
        playPointSound();
        Serial.println(score);
        return;
    }

    else if (nbrOfButtonPush == previousLed + 1)
    {
        score++;
        playPointSound(); 
        showResult(score);
        return;
    }   

    playGameOverSound();
    running = false;
    setAllLeds();
}


void initializeGame()
{
    clearAllLeds();
    currentLed = -1;
    interruptCount = 0;
    buttonNumber = -1;
    running = true;
    score = 0;
    showResult(score);
}

void startTheGame()
{
    initializeGame();
    initializeLeds();
    initializeTimer();
    randomSeed(analogRead(A0));
    showNextLed(); 

    startMelody();   // musiikki alkaa
}

void setup()
{
    Serial.begin(9600);
    initButtonsAndButtonInterrupts();
    initializeLeds();
    Serial.println("Press any game button to start!");

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    initializeDisplay();
}

void startLights()
    {
        setAllLeds();
        delay(500);
        clearAllLeds();
        delay(500);
        setAllLeds();
        delay(500);
        clearAllLeds();
        delay(500);
        setAllLeds();
        delay(500);
        clearAllLeds();
    }

void loop()
{
    unsigned long now = millis();

    if (buttonNumber >= 0)
{
    Serial.print("Button pressed: ");
    Serial.println(buttonNumber);

    // peli alkaa kun nappia 4 painetaan eli pinni 5
    if (idle && buttonNumber == 4)
    {
        idle = false;
        startMillis = now;
        Serial.println("Game starting in 3 seconds...");
    }
    else if (running && buttonNumber >= 1 && buttonNumber <= 4)
    {
        checkGame(buttonNumber);
    }

    buttonNumber = -1;
}


    // Countdown
    if(!idle && !running)
    {
        if(now - startMillis >= 3000)
        {
            startLights();
            startTheGame();
            running = true;
            Serial.println("Game started!");
        }
    }

    if(newTimerInterrupt && running)
    {
        newTimerInterrupt = false;
        clearAllLeds();
        showNextLed();
    }

    playFXLoop();     
    playMelodyLoop();

}
