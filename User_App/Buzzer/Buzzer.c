#include "Buzzer.h"
#include "custom_assert.h"
#include "main.h"

void buzzer_init(void)
{
    // Initialize the STM32 Timer Peripheral
}

void buzzer_play_note(const char* note, const u32 duration_ms)
{
    // Capture the systick timer counter

    // Start the tone generation via the PWM start function
}

void buzzer_mute(void)
{
    // Stop the PWM Signal generation

    // Reset the systick timer
}

void buzzer_play_tone(const u32 tone_frequency_Hz, const u32 duration_ms)
{
    { // Input Checks
        ASSERT(tone_frequency_Hz < 2000);
        ASSERT(tone_frequency_Hz > 100);
        ASSERT(duration_ms >= 1);
        ASSERT(duration_ms < 10000);
    }
}