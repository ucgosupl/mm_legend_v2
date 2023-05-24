/*
 * file:	usart.c
 * author:	GAndaLF
 * brief:	USART peripheral driver.
 */

#include "platform_specific.h"

#include "gpio_f4/gpio_f4.h"

#include "usart.h"

/** USART baud rate. */
#define USART_BAUD_RATE             9600

/** Pin number used for USART TX - PA09. */
#define USART_TX_PIN                9
/** Pin number used for USART RX - PA10. */
#define USART_RX_PIN                10
/** DMA Stream used by USART TX. */
#define USART_DMA                   DMA2_Stream7

/** Mutex serialising access to DMA driver. */
static sem_t tx_sem_bin;

void usart_init(void)
{
    tx_sem_bin = rtos_sem_bin_create();
    rtos_sem_give(tx_sem_bin);

    /* Initialize GPIOs */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    gpio_mode_config(GPIOA, USART_TX_PIN, GPIO_MODE_AF);
    gpio_mode_config(GPIOA, USART_RX_PIN, GPIO_MODE_AF);
    gpio_af_config(GPIOA, USART_TX_PIN, GPIO_AF_USART1);
    gpio_af_config(GPIOA, USART_RX_PIN, GPIO_AF_USART1);

    /* Initialize DMA */
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    NVIC_SetPriority(DMA2_Stream7_IRQn, LOGGER_USART_PRIORITY);
    NVIC_EnableIRQ(DMA2_Stream7_IRQn);

    /* Initialize USART peripheral */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->BRR = APB2_CLOCK_FREQ / USART_BAUD_RATE;
    USART1->CR3 = USART_CR3_DMAT;
    USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

int32_t usart_send_buf(uint8_t *buf, int32_t n_bytes)
{
    if ((buf == NULL) || (n_bytes < 1))
    {
        /* Invalid arguments */
        return -EINVAL;
    }

    if (rtos_sem_take(tx_sem_bin, 10) != true)
    {
        /* Report timeout */
        return -EBUSY;
    }

    USART_DMA->PAR = (uint32_t) &USART1->DR;
    USART_DMA->M0AR = (uint32_t) buf;
    USART_DMA->NDTR = n_bytes;

    USART_DMA->CR = (4 << 25) |         /* Channel 4 */
            (2 << 16) |                 /* Priority high */
            DMA_SxCR_MINC |             /* Memory increment */
            (1 << 6) |                  /* Memory to peripheral */
            DMA_SxCR_TCIE;              /* Transfer complete interrupt enable */

    USART_DMA->CR |= DMA_SxCR_EN;

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

void DMA2_Stream7_IRQHandler(void)
{
    int32_t yield;

    if ((DMA2->HISR & DMA_HISR_TCIF7) != 0)
    {
        /* Clear transfer complete flag and DMA enable flag */
        DMA2->HIFCR |= DMA_HIFCR_CTCIF7;
        USART_DMA->CR &= ~(DMA_SxCR_EN);
        rtos_sem_give_isr(tx_sem_bin, &yield);
    }

    portYIELD_FROM_ISR(yield);
}
