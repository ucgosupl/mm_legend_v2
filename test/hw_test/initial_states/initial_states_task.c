/*
 * file:    initial_states_task.c
 * author:  GAndaLF
 * brief:   Task for initial states measurements.
 */

#include "initial_states_task.h"

#include "platform_specific.h"

#include <stdio.h>

/* Project includes */
#include "button/button.h"
#include "imu/imu.h"

#define SAMPLE_CNT          200

#define POSITION_TEST_TASK_STACKSIZE          (configMINIMAL_STACK_SIZE * 8)
#define POSITION_TEST_TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

struct measure_data
{
    int32_t v_l;
    int32_t v_r;
    int32_t gyro;
};

static struct measure_data measure[SAMPLE_CNT];

static void initial_states_test_task(void *params);

void initial_states_test_task_init(void)
{
    button_init();
    imu_task_init();

    rtos_task_create(initial_states_test_task, "initial",
                     POSITION_TEST_TASK_STACKSIZE, POSITION_TEST_TASK_PRIORITY);
}

static void initial_states_test_task(void *params)
{
    (void) params;

    int32_t i;
    tick_t last;

    /* Collect encoder data every 10ms */
    for (i = 0; i < SAMPLE_CNT; i++)
    {
        last = rtos_tick_count_get();

        measure[i].v_l = encoder_left_read();
        measure[i].v_r = encoder_right_read();
        measure[i].gyro = (int32_t)imu_gyro_z_get()*100;

        rtos_delay_until(&last, 10);
    }

    while (1)
    {
        if (0 != button_1_get())
        {
            rtos_delay(2000);

            for (i = 0; i < SAMPLE_CNT; i++)
            {
                printf("%d\t%d\t%d\n",
                        measure[i].v_l, measure[i].v_r, measure[i].gyro);
            }
        }

        if (0 != button_2_get())
        {
            rtos_delay(10);
        }

        rtos_delay(10);
    }
}
