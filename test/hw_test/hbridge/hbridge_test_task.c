/*
 * file:	hbridge_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing H-bridge functionality.
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
#include "hbridge/hbridge.h"

#include "hbridge_test_task.h"

#define HBRIDGE_TEST_TASK_STACKSIZE         (configMINIMAL_STACK_SIZE * 8)
#define HBRIDGE_TEST_TASK_PRIORITY          (tskIDLE_PRIORITY + 2)

static void hbridge_test_task(void *params);

void hbridge_test_task_init(void)
{
    hbridge_init();

    rtos_task_create(hbridge_test_task, "hbridge",
                     HBRIDGE_TEST_TASK_STACKSIZE, HBRIDGE_TEST_TASK_PRIORITY);
}

static void hbridge_test_task(void *params)
{
    (void) params;

    while (1)
    {
        /* Left forward */
        hbridge_left_speed_set(20);
        hbridge_right_speed_set(0);
        rtos_delay(1000);

        /* Right forward */
        hbridge_left_speed_set(0);
        hbridge_right_speed_set(20);
        rtos_delay(1000);

        /* Left backward */
        hbridge_left_speed_set(-20);
        hbridge_right_speed_set(0);
        rtos_delay(1000);

        /* Right backward */
        hbridge_left_speed_set(0);
        hbridge_right_speed_set(-20);
        rtos_delay(1000);
    }
}
