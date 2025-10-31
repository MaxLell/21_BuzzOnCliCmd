/*
 * Console.h
 *
 * Simple console wrapper providing blocking getchar/putchar implemented
 * on top of STM32 HAL UART interrupt-based API (HAL_UART_Receive_IT /
 * HAL_UART_Transmit_IT).
 *
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

typedef void (*receive_char_fn)(char in_char);

void console_init(receive_char_fn in_receive_char_fn);

int console_putchar(char in_char);

#endif /* CONSOLE_H */
