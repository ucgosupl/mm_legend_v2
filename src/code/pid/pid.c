/*
 * file:	pid.c
 * author:	GAndaLF
 * brief:   PID controller.
 */

#include "platform_specific.h"
#include <math.h>

#include "pid.h"

/** Maximum influence of integral part on output signal in percent. */
#define MAX_I_PART      10

/**
 * Check anti windup of integral part.
 *
 * @param pid               PID controller object.
 */
static void anti_windup(pid_params_t pid);

int32_t pid_init(pid_params_t pid, float p, float i, float d)
{
    if (NULL == pid)
    {
        return -EINVAL;
    }

    pid_reset(pid);

    pid->p = p;
    pid->i = i;
    pid->d = d;

    return 0;
}

void pid_reset(pid_params_t pid)
{
    pid->err_sum = 0;
    pid->y_last = 0;
    pid->u_last = 0;
}

float pid_iter(pid_params_t pid, float setval, float output)
{
    float e;
    float de;
    float u;

    if (NULL == pid)
    {
        return -EINVAL;
    }

    e = setval - output;
    de = pid->y_last - output;
    pid->err_sum += e;

    anti_windup(pid);

    u = pid->u_last + pid->p * e + pid->i * pid->err_sum + pid->d * de;
    pid->y_last = output;
    pid->u_last = u;

    return u;
}

static void anti_windup(pid_params_t pid)
{
    float abs_i;

    abs_i = fabs(pid->i);

    /* Run anti windup only if I is not 0. */
    if (abs_i > 10e-5)
    {
        if (MAX_I_PART / abs_i < pid->err_sum)
        {
            pid->err_sum = MAX_I_PART / abs_i;
        }

        if (-MAX_I_PART  / abs_i > pid->err_sum)
        {
            pid->err_sum = -MAX_I_PART  / abs_i;
        }
    }
}
