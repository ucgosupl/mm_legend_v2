/*
 * File:    gpio_f4.h
 * Author:  GAndaLF
 * Brief:   GPIO configuration functions.
 */

#ifndef _GPIO_F4_H_
#define _GPIO_F4_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup hw_gpio
 * @{
 */

/** GPIO mode of operation - input. */
#define GPIO_MODE_INPUT       0
/** GPIO mode of operation - output. */
#define GPIO_MODE_OUTPUT      1
/** GPIO mode of operation - alternative function. */
#define GPIO_MODE_AF          2
/** GPIO mode of operation - analog input. */
#define GPIO_MODE_ANALOG      3

/** GPIO state change speed - low. */
#define GPIO_SPEED_LOW        0
/** GPIO state change speed - medium. */
#define GPIO_SPEED_MEDIUM     1
/** GPIO state change speed - fast. */
#define GPIO_SPEED_FAST       2
/** GPIO state change speed - high. */
#define GPIO_SPEED_HIGH       3

/** GPIO input pull up/down setting - none. */
#define GPIO_PUPD_NONE        0
/** GPIO input pull up/down setting - pull up. */
#define GPIO_PUPD_PU          1
/** GPIO input pull up/down setting - pull down. */
#define GPIO_PUPD_PD          2

/** GPIO alternative function - JTAG. */
#define GPIO_AF_JTAG          0
/** GPIO alternative function - Microcontroller Clock Output. */
#define GPIO_AF_MCO           0
/** GPIO alternative function - RTC. */
#define GPIO_AF_RTC           0
/** GPIO alternative function - TRACE. */
#define GPIO_AF_TRACE         0
/** GPIO alternative function - Timer 1. */
#define GPIO_AF_TIM1          1
/** GPIO alternative function - Timer 2. */
#define GPIO_AF_TIM2          1
/** GPIO alternative function - Timer 3. */
#define GPIO_AF_TIM3          2
/** GPIO alternative function - Timer 4. */
#define GPIO_AF_TIM4          2
/** GPIO alternative function - Timer 5. */
#define GPIO_AF_TIM5          2
/** GPIO alternative function - Timer 8. */
#define GPIO_AF_TIM8          3
/** GPIO alternative function - Timer 9. */
#define GPIO_AF_TIM9          3
/** GPIO alternative function - Timer 10. */
#define GPIO_AF_TIM10         3
/** GPIO alternative function - Timer 11. */
#define GPIO_AF_TIM11         3
/** GPIO alternative function - I2C 1. */
#define GPIO_AF_I2C1          4
/** GPIO alternative function - I2C 2. */
#define GPIO_AF_I2C2          4
/** GPIO alternative function - I2C 3. */
#define GPIO_AF_I2C3          4
/** GPIO alternative function - SPI 1. */
#define GPIO_AF_SPI1          5
/** GPIO alternative function - SPI 2. */
#define GPIO_AF_SPI2          5
/** GPIO alternative function - I2S 2. */
#define GPIO_AF_I2S2          5
/** GPIO alternative function - I2S 2 EXT. */
#define GPIO_AF_I2S2EXT       5
/** GPIO alternative function - SPI 3. */
#define GPIO_AF_SPI3          6
/** GPIO alternative function - I2S EXT. */
#define GPIO_AF_I2SEXT        6
/** GPIO alternative function - I2S 3. */
#define GPIO_AF_I2S3          6
/** GPIO alternative function - USART 1. */
#define GPIO_AF_USART1        7
/** GPIO alternative function - USART 2. */
#define GPIO_AF_USART2        7
/** GPIO alternative function - USART 3. */
#define GPIO_AF_USART3        7
/** GPIO alternative function - I2S 3 EXT. */
#define GPIO_AF_I2S3EXT       7
/** GPIO alternative function - UART 4. */
#define GPIO_AF_UART4         8
/** GPIO alternative function - UART 5. */
#define GPIO_AF_UART5         8
/** GPIO alternative function - USART6. */
#define GPIO_AF_USART6        8
/** GPIO alternative function - CAN 1. */
#define GPIO_AF_CAN1          9
/** GPIO alternative function - CAN 2. */
#define GPIO_AF_CAN2          9
/** GPIO alternative function - Timer 12. */
#define GPIO_AF_TIM12         9
/** GPIO alternative function - Timer 13. */
#define GPIO_AF_TIM13         9
/** GPIO alternative function - Timer 14. */
#define GPIO_AF_TIM14         9
/** GPIO alternative function - USB On-The-Go Full Speed 1. */
#define GPIO_AF_OTGFS1        10
/** GPIO alternative function - USB On-The-Go High Speed. */
#define GPIO_AF_OTGHS         10
/** GPIO alternative function - Ethernet. */
#define GPIO_AF_ETH           11
/** GPIO alternative function - FSMC. */
#define GPIO_AF_FSMC          12
/** GPIO alternative function - SDIO. */
#define GPIO_AF_SDIO          12
/** GPIO alternative function - USB On-The-Go Full Speed 2. */
#define GPIO_AF_OTGFS2        12
/** GPIO alternative function - DCMI. */
#define GPIO_AF_DCMI          13
/** GPIO alternative function - Alternative function 14. */
#define GPIO_AF_AF14          14
/** GPIO alternative function - Eventout. */
#define GPIO_AF_EVENTOUT      15

/**
 * @brief Function sets GPIO pin mode.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 * @param conf                         Mode to set.
 */
void gpio_mode_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf);

/**
 * @brief Function sets GPIO pin in push-pull mode.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 */
#define gpio_otype_pp_set(gpio, pin)   gpio->OTYPER &= ~(1<<pin);

/**
 * @brief Function sets GPIO pin in open drain mode.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 */
#define gpio_otype_od_set(gpio, pin)   gpio->OTYPER |= (1<<pin);

/**
 * @brief Function sets GPIO pin speed.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 * @param conf                         Speed to set.
 */
void gpio_speed_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf);

/**
 * @brief Function sets GPIO pin pull-up, pull-down.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 * @param conf                         Pull-up, pull down config to set.
 */
void gpio_pupd_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf);

/**
 * @brief Function sets GPIO pin alternative function.
 *
 * @param gpio                         Port to set.
 * @param pin                          Pin to set.
 * @param conf                         Alternative function to set.
 */
void gpio_af_config(GPIO_TypeDef * gpio, int32_t pin, int32_t conf);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GPIO_F4_H_ */
