/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for hw_test_template target.
 */

#include "stm32f4xx.h"
#include "platform_specific.h"

#include "core_init/core_init.h"
#include "logger_test_task.h"

int main(void)
{
    core_init();

    /* Place your initialisation code here. */
    logger_test_task_init();

    /* Place your application code here. */
    vTaskStartScheduler();

    while (1)
        ;
}
