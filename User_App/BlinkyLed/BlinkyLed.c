/*
 * blinky_led.c
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#include "BlinkyLed.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/main.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

#define LED_ON  1
#define LED_OFF 0

static u8 led_state = 0;

void blinkyled_enable()
{
    HAL_GPIO_WritePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin, GPIO_PIN_SET);
    led_state = LED_ON;
}

void blinkyled_disable()
{
    HAL_GPIO_WritePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin, GPIO_PIN_RESET);
    led_state = LED_OFF;
}

void blinkyled_toggle()
{
    led_state = !led_state;
    HAL_GPIO_WritePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin, led_state);
}
