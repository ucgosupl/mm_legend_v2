/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for hw_test_template target.
 */

#include "platform_specific.h"

/* Project includes */
#include "core_init/core_init.h"
#include "logger/logger.h"

#include "wall_test_task.h"

int main(void)
{
    core_init();

    /* Place your initialisation code here. */
    wall_test_task_init();
    logger_task_init();

    /* Place your application code here. */
    vTaskStartScheduler();

    while (1)
        ;
}
