/*
 * File:    gpio_f4.c
 * Author:  GAndaLF
 * Brief:   GPIO configuration functions.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "gpio_f4.h"

void gpio_mode_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf)
{
    gpio->MODER &= ~(3 << (pin << 1));
    gpio->MODER |= conf << (pin << 1);
}

void gpio_speed_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf)
{
    gpio->OSPEEDR &= ~(3 << (pin << 1));
    gpio->OSPEEDR |= conf << (pin << 1);
}

void gpio_pupd_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf)
{
    gpio->PUPDR &= ~(3 << (pin << 1));
    gpio->PUPDR |= conf << (pin << 1);
}

void gpio_af_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf)
{
    if (pin > 7)
    {
        gpio->AFR[1] &= ~(0xF << ((pin - 8) << 2));
        gpio->AFR[1] |= conf << ((pin - 8) << 2);
    }
    else
    {
        gpio->AFR[0] &= ~(0xF << (pin << 2));
        gpio->AFR[0] |= conf << (pin << 2);
    }
}
