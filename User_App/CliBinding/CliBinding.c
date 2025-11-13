#include "CliBinding.h"
#include "../../Utils/EmbeddedCli/src/Cli.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"
#include "../BlinkyLed/BlinkyLed.h"
#include "../Buzzer/Buzzer.h"
#include "../CliBinding/ImperialMarchTheme.h"
#include "../CliBinding/SuperMarioTheme.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ###############################################################
// static function declerations
// ###############################################################

// led cli commands
static int prv_set_led_state(int argc, char* argv[], void* context);
static int prv_play_sound_on_buzzer(int argc, char* argv[], void* context);
static int prv_play_super_mario_theme(int argc, char* argv[], void* context);
static int prv_play_imperial_march_theme(int argc, char* argv[], void* context);
// ###############################################################
// public function definition
// ###############################################################

void clibinding_register_cmds(void)
{
    // Registers als listed commands here to the cli
    cli_binding_t cmds[] = {
        {"set_led_state", prv_set_led_state, NULL, "sets the led state to 'on'/'off'"},
        {"buzzer_play_sound", prv_play_sound_on_buzzer, NULL, "plays a sound on the buzzer 'x Hz', 'x ms'"},
        {"play_mario_theme", prv_play_super_mario_theme, NULL,
         "plays the Super Mario Theme on the buzzer"},
        {"play_imperial_march", prv_play_imperial_march_theme, NULL,
         "plays the Imperial March Theme on the buzzer"},
    };

    u8 cmd_array_size = (sizeof(cmds) / sizeof(cli_binding_t));
    for (u8 i = 0; i < cmd_array_size; ++i)
    {
        // This creates a deep copy of the command and all its related items
        cli_register(&cmds[i]);
    }
}

// ###############################################################
// static function definitions
// ###############################################################

static int prv_set_led_state(int argc, char* argv[], void* context)
{
    ASSERT(argv);

    if (2 != argc)
    {
        // No arguments were given
        cli_print("wrong argument: use: set_led_state 'on' / 'off'\n");
        return CLI_FAIL_STATUS;
    }

    if (0 == strncmp(argv[1], "on", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led enabled\n");
        blinkyled_enable();
    }
    else if (0 == strncmp(argv[1], "off", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led disabled\n");
        blinkyled_disable();
    }
    else
    {
        cli_print("Wrong argument - use 'on' or 'off'\n");
        return CLI_FAIL_STATUS;
    }
    return CLI_OK_STATUS;
}

static int prv_play_sound_on_buzzer(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    if (3 != argc)
    {
        // Not enough arguments were given
        cli_print("Wrong usage: buzzer_play_sound 'x Hz', 'x ms'");
        return CLI_FAIL_STATUS;
    }

    // Parse the frequency string to a number
    // Make the input checks (so for the freq > 100Hz && freq < 2000Hz)
    char* end_ptr;
    u32 frequency_Hz = strtol(argv[1], &end_ptr, 10);
    cli_print("frequency = %d", frequency_Hz);
    if (end_ptr == argv[1])
    {
        // No number was found
        cli_print("wrong frequency entry - please enter a number between 100 and 2000");
        return CLI_FAIL_STATUS;
    }
    if (frequency_Hz < 100 || frequency_Hz > 2000)
    {
        cli_print("frequency entry is out of range - please enter a number between 100 and 2000");
        return CLI_FAIL_STATUS;
    }
    // Parse the tone length string to a number
    // Make the input checks (so for the length > 1ms && length < 10000ms)

    u32 duration_ms = strtol(argv[2], &end_ptr, 10);
    cli_print("duration = %d", duration_ms);
    if (end_ptr == argv[2])
    {
        // No number was found
        cli_print("wrong duration entry - please enter a number between 1 and 10000");
        return CLI_FAIL_STATUS;
    }
    if (duration_ms < 1 && duration_ms > 10000)
    {
        cli_print("duration entry is out of range - please enter a number between 1 and 10000");
        return CLI_FAIL_STATUS;
    }

    // Call the buzzer function
    buzzer_play_sound(frequency_Hz, duration_ms);

    (void)argc;
    (void)argv;

    return CLI_OK_STATUS;
}

static int prv_play_super_mario_theme(int argc, char* argv[], void* context)
{
    ASSERT(argv);

    u32 notes_count = sizeof(super_mario_theme) / sizeof(super_mario_theme[0]);
    for (u32 i = 0; i < notes_count; ++i)
    {
        buzzer_play_sound(super_mario_theme[i].frequency, super_mario_theme[i].duration);
    }
    return CLI_OK_STATUS;
}

static int prv_play_imperial_march_theme(int argc, char* argv[], void* context)
{
    ASSERT(argv);

    u32 notes_count = sizeof(imperial_march_theme) / sizeof(imperial_march_theme[0]);
    for (u32 i = 0; i < notes_count; ++i)
    {
        buzzer_play_sound(imperial_march_theme[i].frequency, imperial_march_theme[i].duration);
    }
    return CLI_OK_STATUS;
}

