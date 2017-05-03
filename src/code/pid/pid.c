/*
 * file:	pid.c
 * author:	GAndaLF
 * brief:   PID controller.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"
#include <stddef.h>

#include "pid.h"

struct
{
    float p;
    float i;
    float d;
    float err;
    float err_sum;
}
pid_params_s;

pid_params_t pid_create(float p, float i, float d)
{
    return NULL;
}

float pid_iter(pid_params_t pid, float setval, float output)
{
    //todo PID calculation.

    return 0.0f;
}
