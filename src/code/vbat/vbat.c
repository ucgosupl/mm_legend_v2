/*
 * file:	vbat.c
 * author:	GAndaLF
 * brief:	Short file description.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "adc/adc.h"
#include "led/led.h"

#include "vbat.h"

#define VBAT_THRESHOLD      1234

static void vbat_task(void *params);

void vbat_task_init(void)
{
    //start vbat task
}

static void vbat_task(void *params)
{
    int32_t vbat_val;

    //todo: add loop and delay
    vbat_val = adc_val_get(ADC_VBAT);

    if (vbat_val < VBAT_THRESHOLD)
    {
        led_on(LED_VBAT);
    }
    else
    {
        led_off(LED_VBAT);
    }
}
