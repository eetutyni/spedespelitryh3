#ifndef MELODY_H
#define MELODY_H


#include <Arduino.h>

// Pää tiedostossa oleva muuttuja
extern bool running;

// Buzzer pinni
const int buzzerPin = 12;
const int groundPin = 13;


const int C4 = 262;
const int D4 = 294;
const int E4 = 330;
const int G4 = 392;
const int MA4 = 440;
const int B4 = 494;
const int C5 = 523;

const int melody[] = {
  E4, E4, D4, D4,
  E4, G4, B4, C4,
  D4, D4, E4, G4,
  E4, C4, D4, D4,
  E4, G4, B4, C4
};

const int duration[] = {
  250, 250, 10, 10,
  200, 200, 250, 250,
  10, 10, 200, 200,
  250, 500, 10, 10,
  200, 200, 200, 200
};


const int pointMelody[] = { G4, C5 };
const int pointDuration[] = { 80, 120 };


const int gameOverMelody[] = { MA4, G4, E4, D4, C4 };
const int gameOverDuration[] = { 200, 200, 200, 250, 600 };


static int noteIndex = 0;
static unsigned long lastNoteTime = 0;
static bool melodyActive = false;

static bool fxActive = false;
static int fxIndex = 0;
static unsigned long fxLastTime = 0;
static const int* fxMelody = nullptr;
static const int* fxDuration = nullptr;
static int fxLength = 0;


void startMelody() {
    noteIndex = 0;
    lastNoteTime = 0;
    melodyActive = true;
}

void stopMelody() {
    melodyActive = false;
    noTone(buzzerPin);
}

void playMelodyLoop() {

    if (!running || !melodyActive || fxActive) {
        return;
    }

    unsigned long now = millis();

    if (lastNoteTime == 0) {
        tone(buzzerPin, melody[noteIndex]);
        lastNoteTime = now;
        return;
    }

    if (now - lastNoteTime >= (unsigned long)duration[noteIndex] + 150) {

        noTone(buzzerPin);
        noteIndex++;

        if (noteIndex >= (int)(sizeof(melody) / sizeof(melody[0]))) {
            noteIndex = 0;
        }

        tone(buzzerPin, melody[noteIndex]);
        lastNoteTime = now;
    }
}


void startFX(const int* mel, const int* dur, int len) {
    fxMelody = mel;
    fxDuration = dur;
    fxLength = len;
    fxIndex = 0;
    fxLastTime = 0;
    fxActive = true;
    noTone(buzzerPin);
}

void playFXLoop() {

    if (!fxActive) return;

    unsigned long now = millis();

    if (fxLastTime == 0) {
        tone(buzzerPin, fxMelody[fxIndex]);
        fxLastTime = now;
        return;
    }

    if (now - fxLastTime >= (unsigned long)fxDuration[fxIndex] + 50) {

        noTone(buzzerPin);
        fxIndex++;

        if (fxIndex >= fxLength) {
            fxActive = false;
            fxLastTime = 0;
            return;
        }

        tone(buzzerPin, fxMelody[fxIndex]);
        fxLastTime = now;
    }
}


void playPointSound() {
    startFX(pointMelody, pointDuration, 2);
}

void playGameOverSound() {
    stopMelody();
    startFX(gameOverMelody, gameOverDuration, 5);
}

#endif