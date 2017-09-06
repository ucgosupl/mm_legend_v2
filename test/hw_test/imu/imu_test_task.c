/*
 * file:	hbridge_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing H-bridge functionality.
 */

#include <stdio.h>

#include "platform_specific.h"

/* Project includes */
#include "logger/logger.h"
#include "imu/imu.h"

#include "imu_test_task.h"

#define IMU_TEST_TASK_STACKSIZE         (configMINIMAL_STACK_SIZE * 8)
#define IMU_TEST_TASK_PRIORITY          (tskIDLE_PRIORITY + 2)

static void imu_test_task(void *params);

void imu_test_task_init(void)
{
    imu_task_init();

    rtos_task_create(imu_test_task, "imu_t", IMU_TEST_TASK_STACKSIZE, IMU_TEST_TASK_PRIORITY);
}

static void imu_test_task(void *params)
{
    (void) params;

    int32_t a_x, a_y, a_z;
    int32_t g_x, g_y, g_z;
    int32_t m_x, m_y, m_z;

    while (1) {
        a_x = (int32_t)(imu_acc_x_get()*100);
        a_y = (int32_t)(imu_acc_y_get()*100);
        a_z = (int32_t)(imu_acc_z_get()*100);

        g_x = (int32_t)(imu_gyro_x_get()*100);
        g_y = (int32_t)(imu_gyro_y_get()*100);
        g_z = (int32_t)(imu_gyro_z_get()*100);

        m_x = (int32_t)(imu_mag_x_get()*100);
        m_y = (int32_t)(imu_mag_y_get()*100);
        m_z = (int32_t)(imu_mag_z_get()*100);

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               a_x, a_y, a_z, g_x, g_y, g_z, m_x, m_y, m_z);

        rtos_delay(500);
    }
}
