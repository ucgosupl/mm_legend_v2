/*
 * file:	led.h
 * author:	GAndaLF
 * brief:	LED controller.
 */

#ifndef _LED_H_
#define _LED_H_

/** Side left IR LED id. */
#define LED_IR_SIDE_L       3
/** Side right IR LED id. */
#define LED_IR_SIDE_R       2
/** Diagonal left IR LED id. */
#define LED_IR_DIAG_L       5
/** Diagonal right IR LED id. */
#define LED_IR_DIAG_R       1
/** Front left IR LED id. */
#define LED_IR_FRONT_L      4
/** Front right IR LED id. */
#define LED_IR_FRONT_R      0
/** Battery voltage LED id. */
#define LED_VBAT            12

/**
 * Initialise LED controller to work.
 */
void led_init(void);

/**
 * Turn on led with a given id.
 *
 * @param id                LED id.
 */
void led_on(int32_t id);

/**
 * Turn off led with a given id.
 *
 * @param id                LED id.
 */
void led_off(int32_t id);

/**
 * Emergency turn off all leds.
 */
void led_all_off(void);

#endif /* _LED_H_ */
