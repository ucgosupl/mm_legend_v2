/*
 * file:	motor.c
 * author:	GAndaLF
 * brief:   Motor control task.
 */

#include "platform_specific.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "encoder/encoder.h"
#include "hbridge/hbridge.h"
#include "pid/pid.h"

#include "motor.h"

/** Maximum allowed motor power. */
#define MOTOR_POWER_MAX     1000

/** Minimum allowed motor power. */
#define MOTOR_POWER_MIN     0

/** Number of cogs in motor gear. */
#define GEAR_MOTOR              10.0f
/** Number of cogs in wheel gear. */
#define GEAR_WHEEL              40.0f
/** Number of encoder ticks per full motor cycle - 16 ticks per cycle, rising and falling edge, A and B. */
#define TICKS_PER_MOTOR_CYCLE   64.0f
/** Circumference of the wheel. */
#define WHEEL_CIRC_MM           69.0f

/** Convert encoder ticks to mm. */
#define TICKS_TO_MM(ticks)      \
    (((ticks) * GEAR_MOTOR * WHEEL_CIRC_MM) / (GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE))

/** Convert mm to encoder ticks. */
#define MM_TO_TICKS(mm)         \
    (((mm) * GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE) / (GEAR_MOTOR * WHEEL_CIRC_MM))

#define SAMPLING_TIME_S 0.010f

/** Forward velocity controller PID proportional gain. */
#define FORWARD_PID_P   2.0f
/** Forward velocity controller PID integral gain. */
#define FORWARD_PID_I   (1.0f * SAMPLING_TIME_S)
/** Forward velocity controller PID derivative gain. */
#define FORWARD_PID_D   (0.0f / SAMPLING_TIME_S)

/** Angular velocity controller PID proportional gain. */
#define ANGULAR_PID_P   1.0f
/** Angular velocity controller PID integral gain. */
#define ANGULAR_PID_I   (1.0f * SAMPLING_TIME_S)
/** Angular velocity controller PID derivative gain. */
#define ANGULAR_PID_D   (0.0f / SAMPLING_TIME_S)

#define MOTOR_ANGULAR_OFFSET    0

#define ROBOT_WIDTH_MM  80.0f

struct motor_params
{
    float vlinear;
    float vangular;

    int32_t vleft_read;
    int32_t vright_read;

    float u_left;
    float u_right;
};

static struct motor_params motor_params;
static struct pid_params forward_pid;
static struct pid_params angular_pid;

static void motor_task(void *params);
static int32_t motor_power_limits(float u);

void motor_task_init(void)
{
    memset(&motor_params, 0, sizeof(struct motor_params));

    pid_init(&forward_pid, FORWARD_PID_P, FORWARD_PID_I, FORWARD_PID_D);
    pid_init(&angular_pid, ANGULAR_PID_P, ANGULAR_PID_I, ANGULAR_PID_D);

    encoder_init();
    hbridge_init();

    rtos_task_create(motor_task, "motor", MOTOR_STACKSIZE, MOTOR_PRIORITY);
}

float motor_vleft_get(void)
{
    return TICKS_TO_MM(motor_params.vleft_read);
}

float motor_vright_get(void)
{
    return TICKS_TO_MM(motor_params.vright_read);
}

void motor_vlinear_set(float val)
{
    motor_params.vlinear = MM_TO_TICKS(2.0f * val * SAMPLING_TIME_S);
}

void motor_vangular_set(float val)
{
    motor_params.vangular = MM_TO_TICKS(val * 2.0f * M_PI *
            ROBOT_WIDTH_MM * SAMPLING_TIME_S / 360.0f);
}

float motor_uleft_get(void)
{
    return motor_params.u_left;
}

float motor_uright_get(void)
{
    return motor_params.u_right;
}

void motor_all_off(void)
{
    hbridge_left_speed_set(0);
    hbridge_right_speed_set(0);
}

static void motor_task(void *params)
{
    (void) params;

    float forward;
    float angle;
    float u_forward = 0;
    float u_angular = 0;
    float u_left = 0;
    float u_right = 0;
    tick_t last;

    while (1)
    {
        last = rtos_tick_count_get();

        motor_params.vleft_read = encoder_left_read();
        motor_params.vright_read = encoder_right_read();

        forward = motor_params.vright_read + motor_params.vleft_read;
        angle = motor_params.vright_read - motor_params.vleft_read;

        /* Forward controller */
        u_forward = pid_iter(&forward_pid, motor_params.vlinear, forward);

        /* Angular controller */
        u_angular = pid_iter(&angular_pid, motor_params.vangular, angle);

        /* Fusion of two controllers */
        u_left = u_forward - u_angular + MOTOR_ANGULAR_OFFSET;
        u_right = u_forward + u_angular - MOTOR_ANGULAR_OFFSET;

        /* Limits */
        motor_params.u_left = motor_power_limits(u_left);
        motor_params.u_right = motor_power_limits(u_right);

        hbridge_left_speed_set(motor_params.u_left);
        hbridge_right_speed_set(motor_params.u_right);

        rtos_delay_until(&last, 10);
    }
}

static int32_t motor_power_limits(float u)
{
    int32_t retval;
    int32_t u_int;

    u_int = (int32_t)u;

    /* Maximum motor power value conditions - bigger values are not handled. */
    if (MOTOR_POWER_MAX < u_int)
    {
        retval = MOTOR_POWER_MAX;
    }
    else if (-MOTOR_POWER_MAX > u_int)
    {
        retval = -MOTOR_POWER_MAX;
    }
    /* Minimum nonzero value condition - lower values might damage motor. */
    else if (MOTOR_POWER_MIN > abs(u_int))
    {
        retval = 0;
    }
    else {
        /* Input value correct, don't need to do anything. */
        retval = u_int;
    }

    return retval;
}
