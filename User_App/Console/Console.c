/*
 * Console.c
 *
 * Implementation of Console_GetChar / console_putchar using HAL_UART_IT
 * This is the file for the HW interface of the cli
 */

#include "Console.h"
#include "../../Core/Inc/usart.h"
#include "../../Utils/EmbeddedUtils/utils/custom_assert.h"
#include "../../Utils/EmbeddedUtils/utils/custom_types.h"

#define UART_HANDLER huart3

/* Single-byte transfer buffers */
static uint8_t u8RxByte = 0u;

static receive_char_fn g_cli_receive_fn = NULL;

void console_init(receive_char_fn in_cli_fn)
{
    ASSERT(in_cli_fn);

    g_cli_receive_fn = in_cli_fn;

    /* Start first RX for one byte so incoming chars are captured */
    if (HAL_UART_Receive_IT(&UART_HANDLER, &u8RxByte, 1) != HAL_OK)
    {
        ASSERT(0);
    }
}

int console_putchar(char in_char)
{
    HAL_UART_Transmit(&UART_HANDLER, (uint8_t*)&in_char, (size_t)1, HAL_MAX_DELAY);
    return 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &UART_HANDLER)
    {
        ASSERT(g_cli_receive_fn);
        g_cli_receive_fn((char)u8RxByte);
        HAL_UART_Receive_IT(&UART_HANDLER, &u8RxByte, (size_t)1);
    }
}
