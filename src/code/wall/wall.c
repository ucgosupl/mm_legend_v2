/*
 * file:	wall.c
 * author:	GAndaLF
 * brief:   Wall detection task.
 */

#include "platform_specific.h"

#include "led/led.h"
#include "photo/photo.h"

#include "wall.h"

static void wall_task(void *params);

void wall_init(void)
{
    led_init();

    rtos_task_create(wall_task, "wall", WALL_STACKSIZE, WALL_PRIORITY);
}

int32_t wall_side_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_side_r_dist_mm_get(void)
{
    return 0;
}

int32_t wall_diag_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_diag_r_dist_mm_get(void)
{
    return 0;
}

int32_t wall_front_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_front_r_dist_mm_get(void)
{
    return 0;
}

static void wall_task(void *params)
{
    (void) params;

    while (1)
    {
        //TODO: change order of lighting leds to avoid interference.
        led_on(LED_IR_FRONT_R);
        rtos_delay(1);
        led_off(LED_IR_FRONT_R);

        led_on(LED_IR_FRONT_L);
        rtos_delay(1);
        led_off(LED_IR_FRONT_L);

        led_on(LED_IR_SIDE_R);
        rtos_delay(1);
        led_off(LED_IR_SIDE_R);

        led_on(LED_IR_SIDE_L);
        rtos_delay(1);
        led_off(LED_IR_SIDE_L);

        led_on(LED_IR_DIAG_R);
        rtos_delay(1);
        led_off(LED_IR_DIAG_R);

        led_on(LED_IR_DIAG_L);
        rtos_delay(1);
        led_off(LED_IR_DIAG_L);
    }
}
