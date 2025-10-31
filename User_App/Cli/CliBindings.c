#include "../../Utils/EmbeddedCli/src/Cli.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"
#include "../BlinkyLed/BlinkyLed.h"

#include <string.h>

int clicmd_led_set_fn(int argc, char* argv[], void* context);

int clicmd_led_set_fn(int argc, char* argv[], void* context)
{
    ASSERT(argv);
    ASSERT(context);

    blinky_led_cfg_t* led_cfg = context;

    if (2 != argc)
    {
        // No arguments were given
        cli_print("wrong argument: use: led_set 'on' / 'off'\n");
        return CLI_FAIL_STATUS;
    }

    if (0 == strncmp(argv[1], "on", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led enabled\n");
        blinkyled_enable(led_cfg);
    }
    else if (0 == strncmp(argv[1], "off", CLI_MAX_RX_BUFFER_SIZE))
    {
        cli_print("Led disabled\n");
        blinkyled_disable(led_cfg);
    }
    else
    {
        cli_print("Wrong argument - use 'on' or 'off'\n");
        return CLI_FAIL_STATUS;
    }
    return CLI_OK_STATUS;
}
