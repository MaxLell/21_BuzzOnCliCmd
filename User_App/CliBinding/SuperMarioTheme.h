/**
 * @file SuperMarioTheme.h
 * 
 * This file contains the Notes for the Super Mario Theme melody.
 * Each note is represented by its frequency in Hertz (Hz) and duration in milliseconds (ms).
 */

#ifndef SUPERMARIOTHEME_H
#define SUPERMARIOTHEME_H

// Super Mario Theme Notes (Frequency in Hz, Duration in ms)
static const struct
{
    unsigned int frequency;
    unsigned int duration;
} super_mario_theme[] = {
    // Main melody
    {659, 150}, // E5
    {659, 150}, // E5
    {0, 150},   // REST
    {659, 150}, // E5
    {0, 150},   // REST
    {523, 150}, // C5
    {659, 150}, // E5
    {0, 150},   // REST
    {784, 150}, // G5
    {0, 450},   // REST
    {392, 150}, // G4
    {0, 450},   // REST

    {523, 150}, // C5
    {0, 300},   // REST
    {392, 150}, // G4
    {0, 300},   // REST
    {330, 150}, // E4
    {0, 300},   // REST
    {440, 150}, // A4
    {0, 150},   // REST
    {494, 150}, // B4
    {0, 150},   // REST
    {466, 150}, // A#4
    {440, 150}, // A4
    {0, 150},   // REST

    {392, 200}, // G4
    {659, 200}, // E5
    {784, 200}, // G5
    {880, 150}, // A5
    {0, 150},   // REST
    {698, 150}, // F5
    {784, 150}, // G5
    {0, 150},   // REST
    {659, 150}, // E5
    {0, 150},   // REST
    {523, 150}, // C5
    {587, 150}, // D5
    {494, 150}, // B4
    {0, 300},   // REST
};

#endif // SUPERMARIOTHEME_H
