/**
 * @file ImperialMarchTheme.h
 * 
 * This file contains the Notes for the Imperial March melody.
 * Each note is represented by its frequency in Hertz (Hz) and duration in milliseconds (ms).
 */

#ifndef IMPERIALMARCHTHEME_H
#define IMPERIALMARCHTHEME_H

// Imperial March Notes (Frequency in Hz, Duration in ms)
static const struct
{
    unsigned int frequency;
    unsigned int duration;
} imperial_march_theme[] = {
    // Imperial March melody
    {392, 500},  // G4
    {392, 500},  // G4
    {392, 500},  // G4
    {311, 350},  // D#4
    {466, 150},  // A#4
    {392, 500},  // G4
    {311, 350},  // D#4
    {466, 150},  // A#4
    {392, 1000}, // G4
    {0, 100},    // REST

    {587, 500},  // D5
    {587, 500},  // D5
    {587, 500},  // D5
    {622, 350},  // D#5
    {466, 150},  // A#4
    {370, 500},  // F#4
    {311, 350},  // D#4
    {466, 150},  // A#4
    {392, 1000}, // G4
    {0, 100},    // REST

    {784, 500}, // G5
    {392, 350}, // G4
    {392, 150}, // G4
    {784, 500}, // G5
    {740, 350}, // F#5
    {698, 150}, // F5
    {659, 150}, // E5
    {622, 150}, // D#5
    {659, 500}, // E5
    {0, 100},   // REST

    {415, 350}, // G#4
    {554, 500}, // C#5
    {523, 350}, // C5
    {494, 150}, // B4
    {466, 150}, // A#4
    {440, 150}, // A4
    {466, 500}, // A#4
    {0, 100},   // REST

    {311, 350},  // D#4
    {370, 500},  // F#4
    {311, 350},  // D#4
    {466, 150},  // A#4
    {392, 500},  // G4
    {311, 350},  // D#4
    {466, 150},  // A#4
    {392, 1000}, // G4
};

#endif // IMPERIALMARCHTHEME_H
