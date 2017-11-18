/*
 * file:	button.c
 * author:	GAndaLF
 * brief:	Hardware driver for buttons.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "button.h"

/** Switch 1 pin number - PB01 */
#define SW1_PIN         1
/** Switch 2 pin number - PB02 */
#define SW2_PIN         2

void button_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    gpio_mode_config(GPIOB, SW1_PIN, GPIO_MODE_INPUT);
    gpio_pupd_config(GPIOB, SW1_PIN, GPIO_PUPD_NONE);

    gpio_mode_config(GPIOB, SW2_PIN, GPIO_MODE_INPUT);
    gpio_pupd_config(GPIOB, SW2_PIN, GPIO_PUPD_NONE);
}

uint32_t button_1_get(void)
{
    return (GPIOB->IDR & (1 << SW1_PIN)) == 0;
}

uint32_t button_2_get(void)
{
    return (GPIOB->IDR & (1 << SW2_PIN)) == 0;
}
