/*
 * file:	motor.c
 * author:	GAndaLF
 * brief:   Motor control task.
 */

#include "platform_specific.h"
#include <string.h>

#include "encoder/encoder.h"
#include "hbridge/hbridge.h"
#include "pid/pid.h"

#include "motor.h"

/** Number of cogs in motor gear. */
#define GEAR_MOTOR              10
/** Number of cogs in wheel gear. */
#define GEAR_WHEEL              40
/** Number of encoder ticks per full motor cycle. */
#define TICKS_PER_MOTOR_CYCLE   16
/** Circumference of the wheel. */
#define WHEEL_CIRC_MM           69

/** Convert encoder ticks to mm. */
#define TICKS_TO_MM(ticks)      \
    (((ticks) * GEAR_MOTOR * WHEEL_CIRC_MM) / (GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE))

/** Convert mm to encoder ticks. */
#define MM_TO_TICKS(mm)         \
    (((mm) * GEAR_WHEEL * TICKS_PER_MOTOR_CYCLE) / (GEAR_MOTOR * WHEEL_CIRC_MM))

/** PID proportional gain. */
#define PID_P   6.6869f
/** PID integral gain. */
#define PID_I   0.0f
/** PID derivative gain. */
#define PID_D   0.03639f

struct motor_params
{
    int32_t vlinear;
    int32_t vangular;

    int32_t vleft_read;
    int32_t vright_read;
};

static struct motor_params motor_params;
static struct pid_params pid_left;
static struct pid_params pid_right;

static void motor_task(void *params);

void motor_task_init(void)
{
    memset(&motor_params, 0, sizeof(struct motor_params));
    pid_init(&pid_left, PID_P, PID_I, PID_D);
    pid_init(&pid_right, PID_P, PID_I, PID_D);

    encoder_init();
    hbridge_init();

    rtos_task_create(motor_task, "motor", MOTOR_STACKSIZE, MOTOR_PRIORITY);
}

int32_t motor_vleft_get(void)
{
    return TICKS_TO_MM(motor_params.vleft_read);
}

int32_t motor_vright_get(void)
{
    return TICKS_TO_MM(motor_params.vright_read);
}

void motor_vlinear_set(float val)
{
    motor_params.vlinear = MM_TO_TICKS(val);
}

void motor_vangular_set(float val)
{
    motor_params.vangular = MM_TO_TICKS(val);
}

static void motor_task(void *params)
{
    (void) params;

    float u_left;
    float u_right;
    tick_t last;

    while (1)
    {
        last = rtos_tick_count_get();

        motor_params.vleft_read = encoder_left_read();
        motor_params.vright_read = encoder_right_read();

        u_left = pid_iter(&pid_left, motor_params.vlinear, motor_params.vleft_read);
        u_right = pid_iter(&pid_right, motor_params.vlinear, motor_params.vright_read);

        hbridge_left_speed_set(u_left);
        hbridge_right_speed_set(u_right);

        rtos_delay_until(&last, 10);
    }
}
