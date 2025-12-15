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
    TCCR1B = (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    OCR1A = 15624;
    TIMSK1 |= (1 << OCIE1A);
    sei();
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
    // Correct: current LED
    if (nbrOfButtonPush == currentLed + 1)
    {
        score++;
        showResult(score);
        playPointSound();      // 🔊 POINT SOUND
        return;
    }

    // Correct: previous LED
    if (nbrOfButtonPush == previousLed + 1)
    {
        score++;
        showResult(score);
        playPointSound();      // 🔊 POINT SOUND
        return;
    }

    // Wrong → game over
    running = false;
    setAllLeds();
    playGameOverSound();       // 🔊 GAME OVER SOUND
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

    startMelody();   // 🎵 background music
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
    for(int i = 0; i < 3; i++)
    {
        setAllLeds();
        delay(500);
        clearAllLeds();
        delay(500);
    }
}

void loop()
{
    unsigned long now = millis();

    // Handle button presses
    if(buttonNumber >= 0)
    {
        Serial.print("Button pressed: ");
        Serial.println(buttonNumber);
        
        if(buttonNumber == 4)
        {
            if(idle)
            {
                idle = false;
                startMillis = now;
                Serial.println("Game starting in 3 seconds...");
            }
        }
        else if(running && buttonNumber >= 1 && buttonNumber <= 4)
        {
            checkGame(buttonNumber);
        }

        buttonNumber = -1;
    }

    // Countdown to start game
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

    // Timer-driven LED update
    if(newTimerInterrupt && running)
    {
        newTimerInterrupt = false;
        clearAllLeds();
        showNextLed();
    }

    playFXLoop();       // 🔊 sound effects engine
    playMelodyLoop();   // 🎵 background melody
}
