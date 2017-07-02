/*
 * file:	hbridge_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing H-bridge functionality.
 */

#include "logger_test_task.h"

#include "platform_specific.h"

/* Project includes */
#include "usart/usart.h"

#define LOGGER_TEST_TASK_STACKSIZE         (configMINIMAL_STACK_SIZE * 8)
#define LOGGER_TEST_TASK_PRIORITY          (tskIDLE_PRIORITY + 2)

#define BUF_SIZE        (4 * 1024)

static uint8_t test_buf[BUF_SIZE];

static void logger_test_task(void *params);

void logger_test_task_init(void)
{
    usart_init();

    rtos_task_create(logger_test_task, "logger",
                     LOGGER_TEST_TASK_STACKSIZE, LOGGER_TEST_TASK_PRIORITY);
}

static void logger_test_task(void *params)
{
    (void) params;

    int32_t i;

    for (i = 0; i < BUF_SIZE; i++)
    {
        test_buf[i] = i;
    }

    while (1)
    {
        usart_send_buf(test_buf, BUF_SIZE);
        rtos_delay(10000);
    }
}
