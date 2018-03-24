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

/** Wall sensor ids. */
enum
{
    WALL_SENSOR_FRONT_R,
    WALL_SENSOR_SIDE_L,
    WALL_SENSOR_DIAG_R,
    WALL_SENSOR_FRONT_L,
    WALL_SENSOR_SIDE_R,
    WALL_SENSOR_DIAG_L,
    WALL_SENSOR_CNT,
};

/** Function converting ADC value to distance for specific sensor. */
typedef int32_t (*adc2dist_fun)(int32_t);

/** Data structure containing wall sensor data. */
struct wall_sensor
{
    int32_t photo_id;
    int32_t led_id;
    adc2dist_fun dist_fun;
    int32_t val;
};

/** All wall sensor data. */
static struct wall_sensor wall_sensor_list[WALL_SENSOR_CNT];

/** Initialize single wall sensor struct. */
static void sensor_list_entry_init(int32_t index, int32_t photo_id, int32_t led_id, adc2dist_fun fun);

/**
 * Wall sensor task handler.
 *
 * @param params            Task parameters - unused.
 */
static void wall_task(void *params);

/**
 * Update single sensor measurement.
 *
 * @param sensor            Sensor data.
 * @param val_off           Ambient light measurement for this sensor.
 */
static void sensor_update(struct wall_sensor *sensor, int32_t val_off);

void wall_init(void)
{
    /* led and adc initialized earlier by vbat task. */

    sensor_list_entry_init(WALL_SENSOR_FRONT_L, ADC_PHOTO_FRONT_L, LED_IR_FRONT_L, adc2dist_front_l);
    sensor_list_entry_init(WALL_SENSOR_FRONT_R, ADC_PHOTO_FRONT_R, LED_IR_FRONT_R, adc2dist_front_r);
    sensor_list_entry_init(WALL_SENSOR_DIAG_L, ADC_PHOTO_DIAG_L, LED_IR_DIAG_L, adc2dist_diag_l);
    sensor_list_entry_init(WALL_SENSOR_DIAG_R, ADC_PHOTO_DIAG_R, LED_IR_DIAG_R, adc2dist_diag_r);
    sensor_list_entry_init(WALL_SENSOR_SIDE_L, ADC_PHOTO_SIDE_L, LED_IR_SIDE_L, adc2dist_side_l);
    sensor_list_entry_init(WALL_SENSOR_SIDE_R, ADC_PHOTO_SIDE_R, LED_IR_SIDE_R, adc2dist_side_r);

    rtos_task_create(wall_task, "wall", WALL_STACKSIZE, WALL_PRIORITY);
}

int32_t wall_side_l_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_SIDE_L].val;
}

int32_t wall_side_r_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_SIDE_R].val;
}

int32_t wall_diag_l_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_DIAG_L].val;
}

int32_t wall_diag_r_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_DIAG_R].val;
}

int32_t wall_front_l_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_FRONT_L].val;
}

int32_t wall_front_r_dist_mm_get(void)
{
    return wall_sensor_list[WALL_SENSOR_FRONT_R].val;
}

static void sensor_list_entry_init(int32_t index, int32_t photo_id, int32_t led_id, adc2dist_fun fun)
{
    wall_sensor_list[index].photo_id = photo_id;
    wall_sensor_list[index].led_id = led_id;
    wall_sensor_list[index].dist_fun = fun;
    wall_sensor_list[index].val = 0;
}

static void wall_task(void *params)
{
    (void) params;

    tick_t last;
    int32_t i;

    int32_t val_off[WALL_SENSOR_CNT];

    while (1)
    {
        last = rtos_tick_count_get();

        /* Measure ambient light. */
        for (i = 0; i < WALL_SENSOR_CNT; i++)
        {
            val_off[i] = adc_val_get(wall_sensor_list[i].photo_id);
        }

        /* Measure distance. */
        for (i = 0; i < WALL_SENSOR_CNT; i++)
        {
            sensor_update(&wall_sensor_list[i], val_off[i]);
        }

        rtos_delay_until(&last, 10);
    }
}

static void sensor_update(struct wall_sensor *sensor, int32_t val_off)
{
    int32_t val_on;

    led_on(sensor->led_id);
    rtos_delay(1);
    val_on = adc_val_get(sensor->photo_id);
    sensor->val = sensor->dist_fun(val_on - val_off);
    led_off(sensor->led_id);
}
