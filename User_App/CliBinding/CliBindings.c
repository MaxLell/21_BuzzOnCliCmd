#include "../../Utils/EmbeddedCli/src/Cli.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"
#include "../BlinkyLed/BlinkyLed.h"
#include "CliBinding.h"

#include <string.h>

// ###############################################################
// static function declerations
// ###############################################################

// led cli commands
static int prv_set_led_state(int argc, char* argv[], void* context);

// buzzer cli commands
static int prv_play_note_on_buzzer(int argc, char* argv[], void* context);
static int prv_play_tone_on_buzzer(int argc, char* argv[], void* context);
static int prv_buzzer_stop(int argc, char* argv[], void* context);
static int prv_mute_buzzer(int argc, char* argv[], void* context);

// ###############################################################
// public function definition
// ###############################################################

void clibinding_register_cmds(const blinky_led_cfg_t* led_cfg_ptr)
{
    // Registers als listed commands here to the cli
    cli_binding_t cmds[] = {
        {"set_led_state", prv_set_led_state, led_cfg_ptr, "sets the led state to 'on'/'off'"},
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
    ASSERT(context);

    blinky_led_cfg_t* led_cfg_ptr = context;

    if (2 != argc)
    {
        // No arguments were given
        cli_print("wrong argument: use: led_set 'on' / 'off'\n");
        return CLI_FAIL_STATUS;
    }

    if (0 == strncmp(argv[1], "on", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led enabled\n");
        blinkyled_enable(led_cfg_ptr);
    }
    else if (0 == strncmp(argv[1], "off", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led disabled\n");
        blinkyled_disable(led_cfg_ptr);
    }
    else
    {
        cli_print("Wrong argument - use 'on' or 'off'\n");
        return CLI_FAIL_STATUS;
    }
    return CLI_OK_STATUS;
}

static int prv_play_note_on_buzzer(int argc, char* argv[], void* context)
{

    ASSERT(argv);
    ASSERT(context);
}

static int prv_play_tone_on_buzzer(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    ASSERT(context);
}

static int clicmd_buzzer_play_tone(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    ASSERT(context);
}

static int prv_buzzer_stop(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    ASSERT(context);
}

static int prv_mute_buzzer(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    ASSERT(context);
}
