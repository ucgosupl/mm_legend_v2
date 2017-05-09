/*
 * file:	logger.h
 * author:	GAndaLF
 * brief:	Logging data to debug USART.
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

/**
 * Initialize logger task to work.
 */
void logger_task_init(void);

/**
 * Print data on debug USART.
 *
 * @param buf           Buffer containing data to be printed.
 * @param len           Length of buffer.
 *
 * @return              Error code.
 */
int32_t logger_write_buffer(uint8_t *buf, int32_t len);

#endif /* _LOGGER_H_ */
