/*
 * file:	motor.c
 * author:	GAndaLF
 * brief:   Motor control task.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "motor.h"

static void motor_task(void *params);

void motor_task_init(void)
{

}

int32_t motor_vleft_get(void)
{
    //todo: return last read encoder value converted to mm/s.
    return 0;
}

int32_t motor_vright_get(void)
{
    //todo: return last read encoder value converted to mm/s.
    return 0;
}

void motor_vlinear_set(float val)
{
    //todo: store expected value
    (void)val;
}

void motor_vangular_set(float val)
{
    //todo: store expected value
    (void)val;
}

static void motor_task(void *params)
{
    (void) params;

    //todo: read data from encoders
    //todo: calculate new speeds for motors using pid
    //todo: set motor speeds
}
