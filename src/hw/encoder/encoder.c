/*
 * file:	encoder.c
 * author:	GAndaLF
 * brief:   Motor encoders driver.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "encoder.h"

/** Encoder 1 channel A pin number - PB04 */
#define ENC_1A_PIN                  4
/** Encoder 1 channel B pin number - PB05 */
#define ENC_1B_PIN                  5
/** Encoder 2 channel A pin number - PB06 */
#define ENC_2A_PIN                  6
/** Encoder 2 channel B pin number - PB07 */
#define ENC_2B_PIN                  7

/**
 * Encoder mode 1 setting in SMS field of TIM->SMCR register.
 *
 * Count up-down only on channel A edge.
 */
#define TIM_SMS_MODE_ENC1           1
/**
 * Encoder mode 2 setting in SMS field of TIM->SMCR register.
 *
 * Count up-down only on channel B edge.
 */
#define TIM_SMS_MODE_ENC2           2
/**
 * Encoder mode 3 setting in SMS field of TIM->SMCR register.
 *
 * Count up-down on edge on either A or B channel.
 */
#define TIM_SMS_MODE_ENC3           3

/** Set Capture/Compare channel to output mode. */
#define TIM_CCxS_MODE_OUT           0
/** Set Capture/Compare channel to input mode mapped on TI1. */
#define TIM_CCxS_MODE_IN_T1         1
/** Set Capture/Compare channel to input mode mapped on TI2. */
#define TIM_CCxS_MODE_IN_T2         2
/** Set Capture/Compare channel to input mode mapped on TRC. */
#define TIM_CCxS_MODE_IN_TRC        3

/** Bit offset of SMS field in SMCR register. */
#define TIM_SMCR_SMS_BIT            0

/** Bit offset of CC1S field in CCMR1 register. */
#define TIM_CCMR1_CC1S_BIT          0
/** Bit offset of CC2S field in CCMR1 register. */
#define TIM_CCMR1_CC2S_BIT          8

/**
 * Initialize GPIOs for encoder inputs.
 */
static void gpio_init(void);

/**
 * Initialize timers for encoder inputs.
 */
static void timer_init(void);

void encoder_init(void)
{
    gpio_init();
    timer_init();
}

int32_t encoder_left_read(void)
{
    int16_t val;

    val = TIM3->CNT;
    TIM3->CNT = 0;

    return (int32_t) val;
}

int32_t encoder_right_read(void)
{
    int16_t val;

    val = TIM4->CNT;
    TIM4->CNT = 0;

    return (int32_t) val;
}

static void gpio_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    gpio_mode_config(GPIOB, ENC_1A_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOB, ENC_1B_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOB, ENC_2A_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOB, ENC_2B_PIN, GPIO_MODE_AF);

    gpio_af_config(GPIOB, ENC_1A_PIN, GPIO_AF_TIM3);
    gpio_af_config(GPIOB, ENC_1B_PIN, GPIO_AF_TIM3);
    gpio_af_config(GPIOB, ENC_2A_PIN, GPIO_AF_TIM4);
    gpio_af_config(GPIOB, ENC_2B_PIN, GPIO_AF_TIM4);
}

static void timer_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;

    /* Select encoder mode */
    TIM3->SMCR = (TIM_SMS_MODE_ENC3 << TIM_SMCR_SMS_BIT);
    TIM4->SMCR = (TIM_SMS_MODE_ENC3 << TIM_SMCR_SMS_BIT);

    /* Set CCR1 as T1, CCR2 as T2 */
    TIM3->CCMR1 = (TIM_CCxS_MODE_IN_T1 << TIM_CCMR1_CC1S_BIT) |
            (TIM_CCxS_MODE_IN_T1 << TIM_CCMR1_CC1S_BIT);
    TIM4->CCMR1 = (TIM_CCxS_MODE_IN_T1 << TIM_CCMR1_CC1S_BIT) |
            (TIM_CCxS_MODE_IN_T1 << TIM_CCMR1_CC1S_BIT);

    /* Configure auto reload, so 0xFFFF is after 0 when downcounting */
    TIM3->ARR = 0xFFFF;
    TIM4->ARR = 0xFFFF;

    /* Enable timers */
    TIM3->CR1 = TIM_CR1_CEN;
    TIM4->CR1 = TIM_CR1_CEN;
}
