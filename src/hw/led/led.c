/*
 * file:	led.c
 * author:	GAndaLF
 * brief:	LED controller.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "led.h"

void led_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    gpio_mode_config(GPIOC, LED_IR_FRONT_L, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, LED_IR_FRONT_R, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, LED_IR_DIAG_L, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, LED_IR_DIAG_R, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, LED_IR_SIDE_L, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, LED_IR_SIDE_R, GPIO_MODE_OUTPUT);

    gpio_mode_config(GPIOC, LED_VBAT, GPIO_MODE_OUTPUT);

    led_all_off();
}

void led_on(int32_t id)
{
    GPIOC->BSRRL = 1 << id;
}

void led_off(int32_t id)
{
    GPIOC->BSRRH = 1 << id;
}

void led_all_off(void)
{
    GPIOC->BSRRH = (1 << (LED_IR_FRONT_L)) |
            (1 << (LED_IR_FRONT_R)) |
            (1 << (LED_IR_DIAG_L)) |
            (1 << (LED_IR_DIAG_R)) |
            (1 << (LED_IR_SIDE_L)) |
            (1 << (LED_IR_SIDE_R)) |
            (1 << (LED_VBAT));
}
