/*
 * file:	console.c
 * author:	GAndaLF
 * brief:   Debug console.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "usart/usart.h"
#include "logger/logger.h"

#include "console.h"

static void console_task(void *params);

void console_task_init(void)
{
    //initialize console task
}

static void console_task(void *params)
{
    //wait for input from debug usart
    //check if input matches predefined command
    //execute command
}
