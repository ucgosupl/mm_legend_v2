/*
 * file:	hbridge.c
 * author:	GAndaLF
 * brief:   H-bridge for motor control module.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "hbridge.h"

/** Motor left PWM pin number - PA01. */
#define MOTOR1_PWM_PIN                  1
/** Motor left dir 1 pin number - PC07. */
#define MOTOR1_CH1_PIN                  7
/** Motor left dir 2 pin number - PC06. */
#define MOTOR1_CH2_PIN                  6

/** Motor right PWM pin number - PA00. */
#define MOTOR2_PWM_PIN                  0
/** Motor right dir 1 pin number - PC08. */
#define MOTOR2_CH1_PIN                  8
/** Motor right dir 2 pin number - PC09. */
#define MOTOR2_CH2_PIN                  9

/** Offset of bitfield CMS MODE in TIM_CR1 register. */
#define TIM_CR1_CMS_MODE_CA3_BIT        5
/** Offset of bitwield OC1M in TIM_CCMR1 register. */
#define TIM_CCMR1_OC1M_BIT              4
/** Offset of bitwield OC2M in TIM_CCMR1 register. */
#define TIM_CCMR1_OC2M_BIT              12

/**
 * Initialize GPIOs for timer and direction pins.
 */
static void gpio_init(void);

/**
 * Initialize hardware timer to PWM mode.
 */
static void timer_init(void);

/**
 * Set motor left direction to forward.
 */
static void motor_left_forward(void);

/**
 * Set motor left direction to backward.
 */
static void motor_left_backward(void);

/**
 * Stop motor left.
 */
static void motor_left_stop(void);

/**
 * Set motor right direction to forward.
 */
static void motor_right_forward(void);

/**
 * Set motor right direction to backward.
 */
static void motor_right_backward(void);

/**
 * Stop motor right.
 */
static void motor_right_stop(void);

void hbridge_init(void)
{
    gpio_init();
    timer_init();
}

uint32_t hbridge_left_speed_set(int32_t speed)
{
    if ((speed > 100) || (speed < -100))
    {
        /* Invalid arguments */
        return -EINVAL;
    }

    if (speed == 0)
    {
        TIM2->CCR2 = 0;
        motor_left_stop();
    }
    else if (speed > 0)
    {
        TIM2->CCR2 = speed;
        motor_left_forward();
    }
    else
    {
        TIM2->CCR2 = -speed;
        motor_left_backward();
    }

    return 0;
}

uint32_t hbridge_right_speed_set(int32_t speed)
{
    if ((speed > 100) || (speed < -100))
    {
        /* Invalid arguments */
        return -EINVAL;
    }

    if (speed == 0)
    {
        TIM2->CCR1 = 0;
        motor_right_stop();
    }
    else if (speed > 0)
    {
        TIM2->CCR1 = speed;
        motor_right_forward();
    }
    else
    {
        TIM2->CCR1 = -speed;
        motor_right_backward();
    }

    return 0;
}

static void gpio_init(void)
{
    /*
     * Motor left:
     *    * CH1 - PC07
     *    * CH2 - PC06
     *    * PWM - PA01
     *
     * Motor right:
     *    * CH1 - PC08
     *    * CH2 - PC09
     *    * PWM - PA00
     */

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    /* PWM pins */
    gpio_mode_config(GPIOA, MOTOR1_PWM_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, MOTOR2_PWM_PIN, GPIO_MODE_AF);
    gpio_af_config(GPIOA, MOTOR1_PWM_PIN, GPIO_AF_TIM2);
    gpio_af_config(GPIOA, MOTOR2_PWM_PIN, GPIO_AF_TIM2);

    /* GPIO pins */
    gpio_mode_config(GPIOC, MOTOR1_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR1_CH2_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR2_CH1_PIN, GPIO_MODE_OUTPUT);
    gpio_mode_config(GPIOC, MOTOR2_CH2_PIN, GPIO_MODE_OUTPUT);

    /* GPIO initial state - all low */
    GPIOC->ODR &= 0xFC3F;
}

static void timer_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->CR1 = (3 << TIM_CR1_CMS_MODE_CA3_BIT);    /* Center aligned mode 3 */
    TIM2->CCMR1 = (6 << TIM_CCMR1_OC1M_BIT) |       /* Channel 1 PWM mode 1 */
            (6 << TIM_CCMR1_OC2M_BIT);              /* Channel 2 PWM mode 1 */
    TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;     /* Output 1 and 2 enabled */

    /* Single timer tick is 1us, full cycle is 100us */
    TIM2->PSC = APB1_CLOCK_FREQ / 1000000 - 1;
    TIM2->ARR = 100;

    /* Set initial duty cycle */
    TIM2->CCR1 = 0;
    TIM2->CCR2 = 0;

    /* Enable timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}

static void motor_left_forward(void)
{
    GPIOC->BSRRH = (1 << MOTOR1_CH1_PIN);
    GPIOC->BSRRL = (1 << MOTOR1_CH2_PIN);
}

static void motor_left_backward(void)
{
    GPIOC->BSRRL = (1 << MOTOR1_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR1_CH2_PIN);
}

static void motor_left_stop(void)
{
    GPIOC->BSRRH = (1 << MOTOR1_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR1_CH2_PIN);
}

static void motor_right_forward(void)
{
    GPIOC->BSRRH = (1 << MOTOR2_CH1_PIN);
    GPIOC->BSRRL = (1 << MOTOR2_CH2_PIN);
}

static void motor_right_backward(void)
{
    GPIOC->BSRRL = (1 << MOTOR2_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR2_CH2_PIN);
}

static void motor_right_stop(void)
{
    GPIOC->BSRRH = (1 << MOTOR2_CH1_PIN);
    GPIOC->BSRRH = (1 << MOTOR2_CH2_PIN);
}
