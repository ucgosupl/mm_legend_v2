/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for hw_test_template target.
 */

#include "platform_specific.h"

/* FreeRTOS includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Project includes */
#include "core_init/core_init.h"
#include "hbridge_test_task.h"

int main(void)
{
    core_init();

    /* Place your initialisation code here. */
    hbridge_test_task_init();

    /* Place your application code here. */
    vTaskStartScheduler();

    while (1)
        ;
}
