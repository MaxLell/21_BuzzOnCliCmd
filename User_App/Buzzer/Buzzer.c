#include "Buzzer.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/main.h"
#include "../../Core/Inc/tim.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

// #####################################################
// Defines
// #####################################################
#define TIM3_PRESCALER (4U)

// #####################################################
// private typedefs
// #####################################################
typedef struct
{
    u32 start_tick_ctr;
    u32 duration_ms;
} delay_non_blocking_cfg_t;

// #####################################################
// private variables
// #####################################################
extern TIM_HandleTypeDef htim3;
static bool is_initialized = false;
static bool is_playing_tone = false;
static delay_non_blocking_cfg_t delay_tone;
static delay_non_blocking_cfg_t delay_freq;

// #####################################################
// private functions
// #####################################################
static u32 prv_calculate_timer_ARR_value(u32 freq_Hz);
static void prv_delay_start(delay_non_blocking_cfg_t* delay, u32 ms);
static bool prv_delay_elapsed(delay_non_blocking_cfg_t* delay);

// #####################################################
// public function implementation
// #####################################################
void buzzer_init(void)
{
    // Assert that the Sys-Clock is 4MHz
    // otherwise the following algorithm does not work
    u32 sysclock_freq_Hz = HAL_RCC_GetSysClockFreq();
    ASSERT(4000000 == sysclock_freq_Hz);

    // Setup the flags
    is_initialized = true;
    is_playing_tone = false;

    // Setup the Prescaler for the timer
    htim3.Instance->PSC = TIM3_PRESCALER;

    // Setup the PAM8904 Driver - see page 5 of the datasheet
    HAL_GPIO_WritePin(BUZZER_EN1_GPIO_Port, BUZZER_EN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BUZZER_EN2_GPIO_Port, BUZZER_EN2_Pin, GPIO_PIN_SET);
}

void buzzer_play_note(const char* note, const u32 duration_ms)
{
    // Capture the systick timer counter

    // Start the tone generation via the PWM start function
}

void buzzer_mute(void)
{
    ASSERT(is_initialized);
    // Stop the PWM Signal generation
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);

    is_playing_tone = false;

    delay_freq.duration_ms = 0;
    delay_freq.start_tick_ctr = 0;
    delay_tone.duration_ms = 0;
    delay_tone.start_tick_ctr = 0;
}

void buzzer_play_tone(const u32 tone_frequency_Hz, const u32 duration_ms)
{
    { // Input Checks
        ASSERT(tone_frequency_Hz < 2000);
        ASSERT(tone_frequency_Hz > 100);
        ASSERT(duration_ms >= 1);
        ASSERT(duration_ms < 10000);
        ASSERT(is_initialized);
    }
    if (!is_playing_tone)
    {
        is_playing_tone = true;

        // Start the non-blocking delay
        prv_delay_start(&delay_freq, duration_ms);

        // Setup the PWM Timer
        u32 arr_value = prv_calculate_timer_ARR_value(tone_frequency_Hz);
        u32 ccr_value = arr_value / 2;    // 50% Dutycycle
        htim3.Instance->ARR = arr_value;  // Timer counter value
        htim3.Instance->CCR1 = ccr_value; // Capture Compare Register
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    }
    else
    {
        bool timer_elapsed = prv_delay_elapsed(&delay_freq);
        if (timer_elapsed)
        {
            // reset the sequence
            is_playing_tone = false;
            HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
        }
    }
}

// #####################################################
// private function implementation
// #####################################################
static u32 prv_calculate_timer_ARR_value(u32 freq_Hz)
{
    ASSERT(is_initialized);

    u32 tmp_ARR_value = 0;
    tmp_ARR_value = (1 * 1000 * 1000) / freq_Hz;
    return tmp_ARR_value;
}

static void prv_delay_start(delay_non_blocking_cfg_t* delay, u32 ms)
{
    ASSERT(delay);
    delay->start_tick_ctr = HAL_GetTick();
    delay->duration_ms = ms;
}

static bool prv_delay_elapsed(delay_non_blocking_cfg_t* delay)
{
    ASSERT(delay);
    return (HAL_GetTick() - delay->start_tick_ctr) >= delay->duration_ms;
}
