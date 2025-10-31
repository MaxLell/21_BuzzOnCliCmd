/*
 * blinky_led.c
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#include "BlinkyLed.h"
#include "../../Core/Inc/main.h"

void BlinkyLed_VerifyArguments(blinky_led_cfg_t* inout_cfg)
{
    ASSERT(inout_cfg);
    ASSERT(inout_cfg->gpio_port);
    ASSERT(inout_cfg->led_state <= E_BLINKY_LED_ON);
}

void blinkyled_enable(blinky_led_cfg_t* inout_cfg)
{
    BlinkyLed_VerifyArguments(inout_cfg);
    HAL_GPIO_WritePin((GPIO_TypeDef*)inout_cfg->gpio_port, (u16)inout_cfg->gpio_pin, GPIO_PIN_SET);
    inout_cfg->led_state = E_BLINKY_LED_ON;
}

void blinkyled_disable(blinky_led_cfg_t* inout_cfg)
{
    BlinkyLed_VerifyArguments(inout_cfg);
    HAL_GPIO_WritePin((GPIO_TypeDef*)inout_cfg->gpio_port, (u16)inout_cfg->gpio_pin, GPIO_PIN_RESET);
    inout_cfg->led_state = E_BLINKY_LED_OFF;
}

void blinkyled_toggle(blinky_led_cfg_t* inout_cfg)
{
    BlinkyLed_VerifyArguments(inout_cfg);
    inout_cfg->led_state = !inout_cfg->led_state;
    HAL_GPIO_WritePin((GPIO_TypeDef*)inout_cfg->gpio_port, (u16)inout_cfg->gpio_pin, (int)inout_cfg->led_state);
}
