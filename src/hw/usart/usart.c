/*
 * file:	usart.c
 * author:	GAndaLF
 * brief:	USART peripheral driver.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "gpio_f4/gpio_f4.h"

#include "usart.h"

/** USART baud rate. */
#define USART_BAUD_RATE             115200

/** Pin number used for USART TX - PA09. */
#define USART_TX_PIN                9
/** Pin number used for USART RX - PA10. */
#define USART_RX_PIN                10

void usart_init(void)
{
    /* Initialize GPIOs */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    gpio_mode_config(GPIOA, USART_TX_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, USART_RX_PIN, GPIO_MODE_AF);
    gpio_af_config(GPIOA, USART_TX_PIN, GPIO_AF_USART1);
    gpio_af_config(GPIOA, USART_RX_PIN, GPIO_AF_USART1);

    /* Initialize USART peripheral */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->BRR = APB2_CLOCK_FREQ / USART_BAUD_RATE;
    USART1->CR1 = USART_CR1_RE | USART_CR1_UE;
}

int32_t usart_send_buf(uint8_t buf, int32_t len)
{
    (void) buf;
    (void) len;

    return 0;
}

uint32_t usart_is_rx_rdy(void)
{
    return !!(USART1->SR & USART_SR_RXNE);
}

uint8_t usart_read_byte(void)
{
    return (uint8_t)USART1->DR;
}
