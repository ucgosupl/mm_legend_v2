/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for main_program target.
 */

#include "platform_specific.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "core_init/core_init.h"
#include "diag/diag.h"

void main(void)
{
    core_init();

    /* Place your initialisation code here. */
    diag_task_init();
    vTaskStartScheduler();

    while (1)
        ;
}
