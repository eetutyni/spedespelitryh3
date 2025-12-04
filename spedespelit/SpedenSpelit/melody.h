#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>

// Pää tiedostossa oleva muuttuja
extern bool running;

// Buzzer pinni
const int buzzerPin = 12;
const int groundPin = 13;

// Nuottien taajuudet (Hz)
const int C4 = 262;
const int D4 = 294;
const int E4 = 330;
const int G4 = 392;
const int B4 = 494;
const int C5 = 523;

// Melodia
const int melody[] = {
  E4, E4, D4, D4,
  E4, G4, B4, C4,
  D4, D4, E4, G4,
  E4, C4, D4, D4,
  E4, G4, B4, C4
};

// Kestot
const int duration[] = {
  250, 250, 10, 10,
  200, 200, 250, 250,
  10, 10, 200, 200,
  250, 500, 10, 10,
  200, 200, 200, 200
};

// Sisäisiä muuttujia melodian toistoon
static int noteIndex = 0;
static unsigned long lastNoteTime = 0;
static bool melodyActive = false;

// Aloita musiikki (kutsutaan pelin startissa)
void startMelody() {
    noteIndex = 0;
    lastNoteTime = 0;
    melodyActive = true;
}

// Soita musiikkia taustalla (kutsutaan loopissa)
void playMelodyLoop() {

    if (!running || !melodyActive) {
        noTone(buzzerPin);
        return;
    }

    unsigned long now = millis();

    // Ensimmäinen nuotti käynnistä heti
    if (lastNoteTime == 0) {
        tone(buzzerPin, melody[noteIndex]);
        lastNoteTime = now;
        return;
    }

    // Nuotin kesto täynnä siirry seuraavaan
    if (now - lastNoteTime >= (unsigned long)duration[noteIndex] + 150) {
        
        noTone(buzzerPin); // tauko

        noteIndex++;

        // Jos melodia loppuu aloita alusta
        if (noteIndex >= (int)(sizeof(melody) / sizeof(melody[0]))) {
            noteIndex = 0;
        }

        tone(buzzerPin, melody[noteIndex]);   // soita seuraava
        lastNoteTime = now;
    }
}

#endif
