/*
 * file:	usart.h
 * author:	GAndaLF
 * brief:	USART peripheral driver.
 */

#ifndef _USART_H_
#define _USART_H_

/**
 * Initialize USART driver to work.
 *
 * This function initializes Tx to work with DMA and Rx to work with polling.
 */
void usart_init(void);

/**
 * Send buffer through USART.
 *
 * @param buf           Buffer to send.
 * @param len           Length of buffer.
 *
 * @return              Error code.
 */
int32_t usart_send_buf(uint8_t *buf, int32_t len);

/**
 * Check if received data is ready to be read.
 *
 * @return              0 - false, true otherwise.
 */
uint32_t usart_is_rx_rdy(void);

/**
 * Read byte from USART.
 *
 * Data is ready to be read if function usart_is_rx_rdy returns true.
 *
 * @return              Data read.
 */
uint8_t usart_read_byte(void);

#endif /* _USART_H_ */
