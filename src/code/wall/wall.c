/*
 * file:	wall.c
 * author:	GAndaLF
 * brief:   Wall detection task.
 */

#include "platform_specific.h"

#include "led/led.h"
#include "adc/adc.h"
#include "adc2dist.h"

#include "wall.h"

/** Data structure containing internal wall module parameters. */
struct wall_params {
    int32_t front_l;
    int32_t front_r;
    int32_t diag_l;
    int32_t diag_r;
    int32_t side_l;
    int32_t side_r;
};

/** Internal wall module parameters. */
PRIVATE struct wall_params wall_data;

/**
 * Wall sensor task handler.
 *
 * @param params            Task parameters - unused.
 */
static void wall_task(void *params);

void wall_init(void)
{
    /* led and adc initialized earlier by vbat task. */

    rtos_task_create(wall_task, "wall", WALL_STACKSIZE, WALL_PRIORITY);
}

int32_t wall_side_l_dist_mm_get(void)
{
    return wall_data.side_l;
}

int32_t wall_side_r_dist_mm_get(void)
{
    return wall_data.side_r;
}

int32_t wall_diag_l_dist_mm_get(void)
{
    return wall_data.diag_l;
}

int32_t wall_diag_r_dist_mm_get(void)
{
    return wall_data.diag_r;
}

int32_t wall_front_l_dist_mm_get(void)
{
    return wall_data.front_l;
}

int32_t wall_front_r_dist_mm_get(void)
{
    return wall_data.front_r;
}

static void wall_task(void *params)
{
    (void) params;

    tick_t last;

    int32_t front_r_off;
    int32_t front_l_off;
    int32_t diag_r_off;
    int32_t diag_l_off;
    int32_t side_r_off;
    int32_t side_l_off;

    int32_t front_r_on;
    int32_t front_l_on;
    int32_t diag_r_on;
    int32_t diag_l_on;
    int32_t side_r_on;
    int32_t side_l_on;

    while (1)
    {
        last = rtos_tick_count_get();

        front_r_off = adc_val_get(ADC_PHOTO_FRONT_R);
        side_l_off = adc_val_get(ADC_PHOTO_SIDE_L);
        diag_r_off = adc_val_get(ADC_PHOTO_DIAG_R);
        front_l_off = adc_val_get(ADC_PHOTO_FRONT_L);
        side_r_off = adc_val_get(ADC_PHOTO_SIDE_R);
        diag_l_off = adc_val_get(ADC_PHOTO_DIAG_L);

        led_on(LED_IR_FRONT_R);
        rtos_delay(1);
        front_r_on = adc_val_get(ADC_PHOTO_FRONT_R);
        wall_data.front_r = adc2dist_front_r(front_r_on - front_r_off);
        led_off(LED_IR_FRONT_R);

        led_on(LED_IR_SIDE_L);
        rtos_delay(1);
        side_l_on = adc_val_get(ADC_PHOTO_SIDE_L);
        wall_data.side_l = adc2dist_side_l(side_l_on - side_l_off);
        led_off(LED_IR_SIDE_L);

        led_on(LED_IR_DIAG_R);
        rtos_delay(1);
        diag_r_on = adc_val_get(ADC_PHOTO_DIAG_R);
        wall_data.diag_r = adc2dist_diag_r(diag_r_on - diag_r_off);
        led_off(LED_IR_DIAG_R);

        led_on(LED_IR_FRONT_L);
        rtos_delay(1);
        front_l_on = adc_val_get(ADC_PHOTO_FRONT_L);
        wall_data.front_l = adc2dist_front_l(front_l_on - front_l_off);
        led_off(LED_IR_FRONT_L);

        led_on(LED_IR_SIDE_R);
        rtos_delay(1);
        side_r_on = adc_val_get(ADC_PHOTO_SIDE_R);
        wall_data.side_r = adc2dist_side_r(side_r_on - side_r_off);
        led_off(LED_IR_SIDE_R);

        led_on(LED_IR_DIAG_L);
        rtos_delay(1);
        diag_l_on = adc_val_get(ADC_PHOTO_DIAG_L);
        wall_data.diag_l = adc2dist_diag_l(diag_l_on - diag_l_off);
        led_off(LED_IR_DIAG_L);

        rtos_delay_until(&last, 10);
    }
}
