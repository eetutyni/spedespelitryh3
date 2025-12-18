#include "buttons.h"
#include "SpedenSpelit.h"


volatile unsigned long lastButtonPressTime[5] = {0,0,0,0,0};

volatile uint8_t lastPortDState = 0;

void initButtonsAndButtonInterrupts(void)
{
    for (byte pin = firstGameButtonPin; pin <= lastGameButtonPin; pin++)
    {
        pinMode(pin, INPUT_PULLUP);
    }

    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT18) |
              (1 << PCINT19) |
              (1 << PCINT20) |
              (1 << PCINT21);

    lastPortDState = PIND;
}



ISR(PCINT2_vect)
{
    unsigned long now = millis();
    uint8_t currentState = PIND;
    uint8_t changed = currentState ^ lastPortDState;
    lastPortDState = currentState;

    // Button 1 (pin 2)
    if (changed & (1 << PD2))
    {
        if (!(currentState & (1 << PD2)) &&
            now - lastButtonPressTime[0] > debounceDelay)
        {
            buttonNumber = 1;
            lastButtonPressTime[0] = now;
        }
    }

    // Button 2 (pin 3)
    if (changed & (1 << PD3))
    {
        if (!(currentState & (1 << PD3)) &&
            now - lastButtonPressTime[1] > debounceDelay)
        {
            buttonNumber = 2;
            lastButtonPressTime[1] = now;
        }
    }

    // Button 3 (pin 4)
    if (changed & (1 << PD4))
    {
        if (!(currentState & (1 << PD4)) &&
            now - lastButtonPressTime[2] > debounceDelay)
        {
            buttonNumber = 3;
            lastButtonPressTime[2] = now;
        }
    }

    // Button 4 (pin 5)
    if (changed & (1 << PD5))
    {
        if (!(currentState & (1 << PD5)) &&
            now - lastButtonPressTime[3] > debounceDelay)
        {
            buttonNumber = 4;
            lastButtonPressTime[3] = now;
        }
    }
}

