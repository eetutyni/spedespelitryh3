#include "buttons.h"
#include "SpedenSpelit.h"
// Last press times for debounce (pins 2-6 → 5 entries)
volatile unsigned long lastButtonPressTime[5] = {0,0,0,0,0};


void initButtonsAndButtonInterrupts(void)
{
    // Set pins as INPUT (external pull-down resistors used)
    for (byte pin = firstGameButtonPin; pin <= lastGameButtonPin; pin++)
    {
        pinMode(pin, INPUT);
    }
    pinMode(startButtonPin, INPUT);

    // Enable Pin Change Interrupts for port D (PCIE2)
    PCICR |= (1 << PCIE2);

    // Enable PCINT for pins 2–6 (PCINT18..PCINT22)
    PCMSK2 |= (1 << PCINT18) | // pin 2
              (1 << PCINT19) | // pin 3
              (1 << PCINT20) | // pin 4
              (1 << PCINT21) | // pin 5
              (1 << PCINT22);  // pin 6
}

// Pin Change Interrupt Handler
ISR(PCINT2_vect)
{
    unsigned long now = millis();

    // pin 2 → button 1
     if (digitalRead(2) == HIGH)
    {
        delayMicroseconds(300);           // small stabilization delay
        if (digitalRead(2) == HIGH && now - lastButtonPressTime[0] > debounceDelay)
        {
            buttonNumber = 1;
            lastButtonPressTime[0] = now;
            return;
        }
    }
  
    // pin 4 → button 3
     if (digitalRead(3) == HIGH)
    {
        delayMicroseconds(300);           // small stabilization delay
        if (digitalRead(3) == HIGH && now - lastButtonPressTime[0] > debounceDelay)
        {
            buttonNumber = 2;
            lastButtonPressTime[0] = now;
            return;
        }
    }
    // pin 5 → button 4
     if (digitalRead(4) == HIGH)
    {
        delayMicroseconds(300);           // small stabilization delay
        if (digitalRead(4) == HIGH && now - lastButtonPressTime[0] > debounceDelay)
        {
            buttonNumber = 3;
            lastButtonPressTime[0] = now;
            return;
        }
    }
    // pin 6 → start button
     if (digitalRead(5) == HIGH)
    {
        delayMicroseconds(300);           // small stabilization delay
        if (digitalRead(5) == HIGH && now - lastButtonPressTime[0] > debounceDelay)
        {
            buttonNumber = 4;
            lastButtonPressTime[0] = now;
            return;
        }
    }
}
