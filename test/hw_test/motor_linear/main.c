/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for hw_test_template target.
 */

#include "platform_specific.h"

/* Project includes */
#include "core_init/core_init.h"
#include "logger/logger.h"
#include "vbat/vbat.h"

#include "motor_linear_task.h"

int main(void)
{
    core_init();

    /* Place your initialisation code here. */
    vbat_task_init();
    motor_linear_task_init();
    logger_task_init();

    /* Place your application code here. */
    vTaskStartScheduler();

    while (1)
        ;
}
