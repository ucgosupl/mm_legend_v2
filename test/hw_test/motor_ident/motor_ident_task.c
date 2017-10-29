/*
 * file:	motor_ident_task.c
 * author:	GAndaLF
 * brief:	Task for motor characteristics identification.
 */

#include "platform_specific.h"

#include <stdio.h>

/* Project includes */
#include "button/button.h"
#include "encoder/encoder.h"
#include "hbridge/hbridge.h"
#include "imu/imu.h"

#include "motor_ident_task.h"

/* Base speed passed to both motors - responsible for linear velocity. */
#define MOTOR_SPEED_BASE        40
/* Speed added to left motor and subtracted from right - responsible for angular velocity. */
#define MOTOR_SPEED_OFFSET      10
/* Number of samples gathered in a single measurement. */
#define SAMPLE_CNT              100

#define MOTOR_IDENT_TASK_STACKSIZE          (configMINIMAL_STACK_SIZE * 8)
#define MOTOR_IDENT_TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

struct read_params
{
    int32_t left;
    int32_t right;
    int32_t rot_z;
};

static struct read_params read_data[SAMPLE_CNT];

static void motor_ident_task(void *params);

void motor_ident_task_init(void)
{
    button_init();
    encoder_init();
    hbridge_init();
    imu_task_init();

    rtos_task_create(motor_ident_task, "motor",
                     MOTOR_IDENT_TASK_STACKSIZE, MOTOR_IDENT_TASK_PRIORITY);
}

static void motor_ident_task(void *params)
{
    (void) params;

    int32_t i;
    tick_t last;

    while (1)
    {
        if (0 != button_1_get())
        {
            rtos_delay(2000);

            /* Reset encoders before measurement */
            encoder_left_read();
            encoder_right_read();

            hbridge_left_speed_set(MOTOR_SPEED_BASE + MOTOR_SPEED_OFFSET);
            hbridge_right_speed_set(MOTOR_SPEED_BASE - MOTOR_SPEED_OFFSET);

            /* Collect encoder data every 10ms */
            for (i = 0; i < SAMPLE_CNT; i++)
            {
                last = rtos_tick_count_get();

                read_data[i].left = encoder_left_read();
                read_data[i].right = encoder_right_read();
                read_data[i].rot_z = (int32_t)(imu_gyro_z_get() * 100.0f);

                rtos_delay_until(&last, 10);
            }

            hbridge_left_speed_set(0);
            hbridge_right_speed_set(0);

            for (i = 0; i < SAMPLE_CNT; i++)
            {
                printf("%d\t%d\t%d\n", read_data[i].left, read_data[i].right, read_data[i].rot_z);
            }
        }

        if (0 != button_2_get())
        {
            rtos_delay(10);
        }

        rtos_delay(10);
    }
}
