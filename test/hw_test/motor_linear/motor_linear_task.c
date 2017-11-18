/*
 * file:    motor_linear_task.c
 * author:  GAndaLF
 * brief:   Task for checking linear velocity control loop.
 */

#include "motor_linear_task.h"

#include "platform_specific.h"

#include <stdio.h>

/* Project includes */
#include "button/button.h"
#include "motor/motor.h"
#include "imu/imu.h"



#define SPEED_MM_MS         70
#define SPEED_ANGULAR       90
#define SAMPLE_CNT          200

#define MOTOR_IDENT_TASK_STACKSIZE          (configMINIMAL_STACK_SIZE * 8)
#define MOTOR_IDENT_TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

struct motor_params
{
    int32_t left;
    int32_t right;
    int32_t ang;
};

static struct motor_params encoder_data[SAMPLE_CNT];
static struct motor_params u_data[SAMPLE_CNT];

static void motor_linear_task(void *params);

void motor_linear_task_init(void)
{
    button_init();
    imu_task_init();
    motor_task_init();

    rtos_task_create(motor_linear_task, "motor_l",
                     MOTOR_IDENT_TASK_STACKSIZE, MOTOR_IDENT_TASK_PRIORITY);
}

static void motor_linear_task(void *params)
{
    (void) params;

    int32_t i;
    tick_t last;

    while (1)
    {
        if (0 != button_1_get())
        {
            rtos_delay(2000);

            motor_vlinear_set(SPEED_MM_MS);
            motor_vangular_set(SPEED_ANGULAR);

            /* Collect encoder data every 10ms */
            for (i = 0; i < SAMPLE_CNT; i++)
            {
                last = rtos_tick_count_get();

                encoder_data[i].left = (int32_t)motor_vleft_get();
                encoder_data[i].right = (int32_t)motor_vright_get();
                encoder_data[i].ang = (int32_t)(imu_gyro_z_get()*100.0);

                u_data[i].left = (int32_t)motor_uleft_get();
                u_data[i].right = (int32_t)motor_uright_get();

                rtos_delay_until(&last, 10);
            }

            motor_vlinear_set(0);
            motor_vangular_set(0);

            for (i = 0; i < SAMPLE_CNT; i++)
            {
                printf("%d\t%d\t%d\t%d\t%d\n", encoder_data[i].left, encoder_data[i].right,
                        encoder_data[i].ang, u_data[i].left, u_data[i].right);
            }
        }

        if (0 != button_2_get())
        {
            rtos_delay(10);
        }

        rtos_delay(10);
    }
}
