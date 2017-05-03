/*
 * file:	imu.c
 * author:	GAndaLF
 * brief:   Task reading data from IMU sensor.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "i2c_master/i2c_master.h"

#include "imu.h"

static void imu_task(void *params);

void imu_task_init(void)
{

}

float imu_acc_x_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_acc_y_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_acc_z_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_gyro_x_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_gyro_y_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_gyro_z_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_mag_x_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_mag_y_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

float imu_mag_z_get(void)
{
    //todo: convert reading to proper units
    return 0.0f;
}

static void imu_task(void *params)
{
    (void) params;

    //read sensors in loop
}
