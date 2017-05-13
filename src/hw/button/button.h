/*
 * file:	button.h
 * author:	GAndaLF
 * brief:	Hardware driver for buttons.
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

/**
 * Initialise button pins to work.
 */
void button_init(void);

/**
 * Get state of button 1 pin.
 *
 * @return          Button state - 1 - released, 0 - pushed.
 */
uint32_t button_1_get(void);

/**
 * Get state of button 2 pin.
 *
 * @return          Button state - 1 - released, 0 - pushed.
 */
uint32_t button_2_get(void);

#endif /* _BUTTON_H_ */
