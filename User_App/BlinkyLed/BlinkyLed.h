/*
 * blinky_led.h
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#ifndef BLINKYLED_BLINKYLED_H_
#define BLINKYLED_BLINKYLED_H_

#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

/**
 * @brief LED state enumeration for BlinkyLed module.
 */
typedef enum
{
    E_BLINKY_LED_OFF = 0,
    E_BLINKY_LED_ON = 1
} blinky_led_state_e;

/**
 * @brief Configuration structure for a Blinky LED instance.
 *
 * Holds the state and hardware configuration for a single LED.
 */
typedef struct
{
    blinky_led_state_e led_state;
    void *gpio_port;
    u16 gpio_pin;
} blinky_led_cfg_t;

/**
 * @brief Turns the LED on.
 *
 * Sets the GPIO pin to the active state and updates the configuration.
 * @param[in,out] inout_pSelf Pointer to the LED configuration structure.
 */
void blinkyled_enable(blinky_led_cfg_t *inout_pSelf);

/**
 * @brief Turns the LED off.
 *
 * Sets the GPIO pin to the inactive state and updates the configuration.
 * @param[in,out] inout_pSelf Pointer to the LED configuration structure.
 */
void blinkyled_disable(blinky_led_cfg_t *inout_pSelf);

/**
 * @brief Toggles the LED state.
 *
 * Inverts the current state of the LED and updates the hardware and
 * configuration.
 * @param[in,out] inout_pSelf Pointer to the LED configuration structure.
 */
void blinkyled_toggle(blinky_led_cfg_t *inout_pSelf);

#endif /* BLINKYLED_BLINKYLED_H_ */
