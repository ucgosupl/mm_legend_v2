/*
 * file:    position_task.c
 * author:  GAndaLF
 * brief:   Task for position estimation hardware test.
 */

#include "position_task.h"

#include "platform_specific.h"

#include <stdio.h>

/* Project includes */
#include "button/button.h"
#include "motor/motor.h"
#include "imu/imu.h"
#include "position/position.h"

#define SPEED_MM_MS         15
#define SPEED_ANGULAR       30
#define SAMPLE_CNT          200

#define POSITION_TEST_TASK_STACKSIZE          (configMINIMAL_STACK_SIZE * 8)
#define POSITION_TEST_TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

struct position_params
{
    int32_t x;
    int32_t y;
    int32_t alpha;
    int32_t v;
    int32_t omega;
};

struct measure_data
{
    int32_t v_l;
    int32_t v_r;
    int32_t gyro;
};

static struct position_params position[SAMPLE_CNT];
static struct measure_data measure[SAMPLE_CNT];

static void position_test_task(void *params);

void position_test_task_init(void)
{
    button_init();
    imu_task_init();
    motor_task_init();
    position_task_init();

    rtos_task_create(position_test_task, "pos_test",
                     POSITION_TEST_TASK_STACKSIZE, POSITION_TEST_TASK_PRIORITY);
}

static void position_test_task(void *params)
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

                position[i].x = (int32_t)position_x_get();
                position[i].y = (int32_t)position_y_get();
                position[i].alpha = (int32_t)position_alpha_get();
                position[i].v = (int32_t)position_v_get();
                position[i].omega = (int32_t)position_omega_get();

                measure[i].v_l = (int32_t)motor_vleft_get();
                measure[i].v_r = (int32_t)motor_vright_get();
                measure[i].gyro = (int32_t)imu_gyro_z_get()*100;

                rtos_delay_until(&last, 10);
            }

            motor_vlinear_set(0);
            motor_vangular_set(0);

            for (i = 0; i < SAMPLE_CNT; i++)
            {
                printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", position[i].x, position[i].y,
                        position[i].alpha, position[i].v, position[i].omega,
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
