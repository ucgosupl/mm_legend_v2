/*
 * file:	motor.c
 * author:	GAndaLF
 * brief:   Motor control task.
 */

#include "platform_specific.h"
#include <string.h>
#include <stdlib.h>

#include "encoder/encoder.h"
#include "hbridge/hbridge.h"
#include "pid/pid.h"
#include "imu/imu.h"

#include "motor.h"

/** Maximum allowed motor power. */
#define MOTOR_POWER_MAX     1000

/** Minimum allowed motor power. */
#define MOTOR_POWER_MIN     150

/** Number of cogs in motor gear. */
#define GEAR_MOTOR              10.0f
/** Number of cogs in wheel gear. */
#define GEAR_WHEEL              40.0f
/** Number of encoder ticks per full motor cycle - 16 ticks per cycle, rising and falling edge. */
#define TICKS_PER_MOTOR_CYCLE   32.0f
/** Circumference of the wheel. */
#define WHEEL_CIRC_MM           69.0f

/** Convert encoder ticks to mm. */
#define TICKS_TO_MM(ticks)      \
    (((ticks) * GEAR_MOTOR * WHEEL_CIRC_MM) / (GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE))

/** Convert mm to encoder ticks. */
#define MM_TO_TICKS(mm)         \
    (((mm) * GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE) / (GEAR_MOTOR * WHEEL_CIRC_MM))

/** Forward velocity controller PID proportional gain. */
#define FORWARD_PID_P   15.496f
/** Forward velocity controller PID integral gain. */
#define FORWARD_PID_I   0.0f
/** Forward velocity controller PID derivative gain. */
#define FORWARD_PID_D   0.1f

/** Angular velocity controller PID proportional gain. */
#define ANGULAR_PID_P   -1.4320f
/** Angular velocity controller PID integral gain. */
#define ANGULAR_PID_I   0.0f
/** Angular velocity controller PID derivative gain. */
#define ANGULAR_PID_D   0.1f

#define MOTOR_ANGULAR_OFFSET    -15

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
static struct pid_params forward_pid_left;
static struct pid_params forward_pid_right;
static struct pid_params angular_pid;

static void motor_task(void *params);
static int32_t motor_power_limits(float u);

void motor_task_init(void)
{
    memset(&motor_params, 0, sizeof(struct motor_params));

    pid_init(&forward_pid_left, FORWARD_PID_P, FORWARD_PID_I, FORWARD_PID_D);
    pid_init(&forward_pid_right, FORWARD_PID_P, FORWARD_PID_I, FORWARD_PID_D);

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
    motor_params.vlinear = MM_TO_TICKS(val);
}

void motor_vangular_set(float val)
{
    motor_params.vangular = val;
}

float motor_uleft_get(void)
{
    return motor_params.u_left;
}

float motor_uright_get(void)
{
    return motor_params.u_right;
}

static void motor_task(void *params)
{
    (void) params;

    float gyro_z;
    float u_left_f;
    float u_right_f;
    float u_angular;
    tick_t last;

    while (1)
    {
        last = rtos_tick_count_get();

        motor_params.vleft_read = encoder_left_read();
        motor_params.vright_read = encoder_right_read();
        gyro_z = -imu_gyro_z_get();

        /* Forward controller */
        u_left_f = pid_iter(&forward_pid_left, motor_params.vlinear, motor_params.vleft_read);
        u_right_f = pid_iter(&forward_pid_right, motor_params.vlinear, motor_params.vright_read);

        /* Angular controller */
        u_angular = pid_iter(&angular_pid, motor_params.vangular, gyro_z);

        /* Fusion of two controllers */
        u_left_f = u_left_f + u_angular + MOTOR_ANGULAR_OFFSET;
        u_right_f = u_right_f - u_angular - MOTOR_ANGULAR_OFFSET;

        /* Limits */
        motor_params.u_left = motor_power_limits(u_left_f);
        motor_params.u_right = motor_power_limits(u_right_f);

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
