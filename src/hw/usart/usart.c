/*
 * file:	usart.c
 * author:	GAndaLF
 * brief:	USART peripheral driver.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "usart.h"

void usart_init(void)
{

}

int32_t usart_send_buf(uint8_t buf, int32_t len)
{
    (void) buf;
    (void) len;

    return 0;
}

uint32_t usart_is_rx_rdy(void)
{
    return 0;
}

uint8_t usart_read_byte(void)
{
    return 0;
}
