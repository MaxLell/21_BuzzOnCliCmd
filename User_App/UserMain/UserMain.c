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
#include "../BlinkyLed/BlinkyLed.h"
#include "../Console/Console.h"

extern int clicmd_led_set_fn(int argc, char* argv[], void* context);

void assertion(const char* file, uint32_t line, const char* expr)
{
    cli_print("Assertion failed in file %s on line %lu: %s\r\n", file, line, expr);
    // Add a breakpoint here for debugging
    __asm("BKPT #0");
    while (1)
    {
    }
}

static blinky_led_cfg_t led;

static cli_cfg_t cli_cfg;

static void prv_init()
{
    // initialize the asserts
    custom_assert_init(assertion);

    // Initialize the led
    led.gpio_port = BLINKY_LED_GPIO_Port;
    led.gpio_pin = BLINKY_LED_Pin;
    led.led_state = E_BLINKY_LED_OFF;

    // Initialize the Console
    // (the hw interface for the cli)
    console_init(cli_receive);

    // Initialize the cli
    cli_init(&cli_cfg, console_putchar);

    // Register the command
    cli_binding_t led_cmd = {
        .name = "led_set",
        .help = "Set the state of the LED: led_set 'on' / 'off'",
        .cmd_fn = clicmd_led_set_fn,
        .context = &led,
    };
    cli_register(&led_cmd);
}

static void prv_loop() { cli_process(); }

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
