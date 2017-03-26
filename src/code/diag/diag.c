/*
 * file:    diag.c
 * author:  GAndaLF
 * brief:   Source file for diagnostic task.
 */

#include "platform_specific.h"
#include "priority.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "diag.h"

/**
 * @addtogroup code_diag
 *
 * @{
 */

/**
 * Diagnostic task.
 *
 * @param params        Params for the task, unused.
 */
static void
diag_task(void * params);

void
diag_task_init(void)
{
    rtos_task_create(diag_task, "diag", DIAG_STACKSIZE, DIAG_PRIORITY);
}

static void
diag_task(void * params)
{
    (void)params;

    /* It is possible to decrease priority after initialization. */

    while (1) {
        /* Checks could be added here. For example watchdog handler. */
        rtos_delay(5000);
    }
}

/**
 * @}
 */
