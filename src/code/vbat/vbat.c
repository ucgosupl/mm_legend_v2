/*
 * file:	vbat.c
 * author:	GAndaLF
 * brief:	Short file description.
 */

#include "platform_specific.h"

#include "adc/adc.h"
#include "led/led.h"
#include "motor/motor.h"

#include "vbat.h"

/** Value of voltage divider upper resistance. */
#define VBAT_DIV_UP_KOHM        100UL
/** Value of voltage divider lower resistance. */
#define VBAT_DIV_DOWN_KOHM      51UL
/** Minimum allowed battery voltage in millivolts. */
#define VBAT_MIN_VOLTAGE_MV     7000UL

/** Minimum allowed value read from ADC. */
#define VBAT_THRESHOLD  \
    ((VBAT_DIV_DOWN_KOHM * VBAT_MIN_VOLTAGE_MV * ADC_MAX_VAL) / \
((VBAT_DIV_UP_KOHM + VBAT_DIV_DOWN_KOHM) * ADC_MAX_VOLTAGE_MV))

PRIVATE void vbat_task(void *params);

void vbat_task_init(void)
{
    led_init();
    adc_init();

    rtos_task_create(vbat_task, "vbat", VBAT_STACKSIZE, VBAT_PRIORITY);
}

PRIVATE void vbat_task(void *params)
{
    (void) params;

    tick_t tick_cnt;
    int32_t vbat_val;
    int32_t low_voltage_timeout;

    low_voltage_timeout = 0;
    while (1)
    {
        tick_cnt = rtos_tick_count_get();

        //TODO: check threshold with real values
        vbat_val = adc_val_get(ADC_VBAT);
        if (vbat_val < (int32_t)VBAT_THRESHOLD)
        {
            led_off(LED_VBAT);

            low_voltage_timeout++;
            if (5 <= low_voltage_timeout)
            {
                rtos_critical_section_enter();
                motor_all_off();
                led_all_off();

                while (1)
                {
                    TEST_ENDLESS_LOOP();
                }
            }
        }
        else
        {
            led_on(LED_VBAT);

            low_voltage_timeout = 0;
        }

        rtos_delay_until(&tick_cnt, 100);
    }
}
