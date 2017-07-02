/*
 * file:	logger.c
 * author:	GAndaLF
 * brief:	Logging data to debug USART.
 */

#include "platform_specific.h"

#include "usart/usart.h"

#include "logger.h"

static void logger_task(void *params);

void logger_task_init(void)
{
    usart_init();

    //init logger task
}

int32_t logger_write_buffer(uint8_t *buf, int32_t len)
{
    //copy data to internal buffer
}

static void logger_task(void *params)
{
    (void) params;

    //send internal buffer to usart driver
}
