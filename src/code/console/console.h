/*
 * file:	console.h
 * author:	GAndaLF
 * brief:	Debug console.
 */

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/**
 * Initialize console task.
 *
 * Console task runs debug console allowing user to send commands to the system
 * via debug USART.
 */
void console_task_init(void);

#endif /* _CONSOLE_H_ */
