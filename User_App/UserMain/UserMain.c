/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_MAIN_C_
#define USER_MAIN_C_

#include "../../Core/Inc/main.h"
#include "../../Utils/EmbeddedCli/src/Cli.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../Buzzer/Buzzer.h"
#include "../CliBinding/CliBinding.h"
#include "../Console/Console.h"

void assertion(const char* file, uint32_t line, const char* expr)
{
    cli_print("Assertion failed in file %s on line %lu: %s\r\n", file, line, expr);
    // Add a breakpoint here for debugging
    __asm("BKPT #0");
    while (1)
    {
    }
}

static cli_cfg_t cli_cfg;

static void prv_init()
{
    // initialize the asserts
    custom_assert_init(assertion);

    // Initialize the Console
    // (the hw interface for the cli)
    console_init(cli_receive);

    // Initialize the cli
    cli_init(&cli_cfg, console_putchar);

    // Initialize the Buzzer
    buzzer_init();

    // Initialize the cli cmds
    clibinding_register_cmds();
}

static void prv_loop()
{ // All the action only happens in the cli commands
    cli_process();
}

void user_main(void)
{
    // Init
    prv_init();

    // Loop
    for (;;)
    {
        prv_loop();
    }
}

#endif /* USER_MAIN_C_ */
