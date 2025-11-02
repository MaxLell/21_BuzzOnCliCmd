#include "Buzzer.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/main.h"
#include "../../Core/Inc/tim.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

// #####################################################
typedef struct
{
    u32 start_tick_ctr;
    u32 duration_ms;
} delay_non_blocking_cfg_t;

// #####################################################
// private variables
// #####################################################
extern TIM_HandleTypeDef htim1;
static bool is_initialized = false;
static bool is_playing_tone = false;
static delay_non_blocking_cfg_t delay_tone;
static delay_non_blocking_cfg_t delay_freq;

// #####################################################
// Defines
// #####################################################
#define BUZZER_TIM_PRESCALER (3)
#define BUZZER_TIM_HANDLE    (htim1)
#define BUZZER_TIM_CHANNEL   (TIM_CHANNEL_3)

// #####################################################
// private typedefs

// #####################################################
// private functions
// #####################################################
static u32 prv_calculate_timer_ARR_value(u32 freq_Hz);

// #####################################################
// public function implementation
// #####################################################
void buzzer_init(void)
{
    // Assert that the Sys-Clock is 4MHz
    // otherwise the following implementation does not work
    u32 sysclock_freq_Hz = HAL_RCC_GetSysClockFreq();
    ASSERT(4000000 == sysclock_freq_Hz);

    // Setup the flags
    is_initialized = true;
    is_playing_tone = false;

    // Setup the Prescaler for the timer
    __HAL_TIM_PRESCALER(&BUZZER_TIM_HANDLE, BUZZER_TIM_PRESCALER);

    // Setup the PAM8904 Driver - see page 5 of the datasheet
    // https://www.mikroe.com/buzz-3-click
    // https://download.mikroe.com/documents/add-on-boards/click/buzz_3_click/buzz-3-click-schematic-v100.pdf
    // https://download.mikroe.com/documents/datasheets/PAM8904_datasheet.pdf

    HAL_GPIO_WritePin(BUZZER_EN1_GPIO_Port, BUZZER_EN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BUZZER_EN2_GPIO_Port, BUZZER_EN2_Pin, GPIO_PIN_SET);

    HAL_StatusTypeDef status = HAL_TIM_PWM_Start(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);
    ASSERT(HAL_OK == status);
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
    HAL_TIM_PWM_Stop(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);

    is_playing_tone = false;

    delay_freq.duration_ms = 0;
    delay_freq.start_tick_ctr = 0;
    delay_tone.duration_ms = 0;
    delay_tone.start_tick_ctr = 0;
}

void buzzer_play_sound(const u32 tone_frequency_Hz, const u32 duration_ms)
{
    { // Input Checks
        ASSERT(tone_frequency_Hz < 2000);
        ASSERT(tone_frequency_Hz > 100);
        ASSERT(duration_ms >= 1);
        ASSERT(duration_ms < 10000);
        ASSERT(is_initialized);
    }
    // Setup the PWM Timer
    u32 arr_value = prv_calculate_timer_ARR_value(tone_frequency_Hz);
    u32 ccr_value = arr_value / 2; // 50% Dutycycle
    __HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM_HANDLE, arr_value);
    __HAL_TIM_SET_COMPARE(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL, ccr_value);

    // Play the sound
    HAL_StatusTypeDef status = HAL_TIM_PWM_Start(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);
    ASSERT(HAL_OK == status);
    HAL_Delay(duration_ms);
    status = HAL_TIM_PWM_Stop(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);
    ASSERT(HAL_OK == status);
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
