#ifndef BUZZER_H
#define BUZZER_H

#include "custom_types.h"

void buzzer_init(void);

void buzzer_play_note(const char* note, const u32 duration_ms);

void buzzer_play_sound(const u32 tone_frequency_Hz, const u32 duration_ms);

void buzzer_mute(void);

#endif // BUZZER_H