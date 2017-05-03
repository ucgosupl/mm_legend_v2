/*
 * file:	led.h
 * author:	GAndaLF
 * brief:	LED controller.
 */

#ifndef _LED_H_
#define _LED_H_

/** Channel used by side left IR LED. */
#define LED_IR_SIDE_L       0
/** Channel used by side right IR LED. */
#define LED_IR_SIDE_R       1
/** Channel used by diagonal left IR LED. */
#define LED_IR_DIAG_L       2
/** Channel used by diagonal right IR LED. */
#define LED_IR_DIAG_R       3
/** Channel used by front left IR LED. */
#define LED_IR_FRONT_L      4
/** Channel used by front right IR LED. */
#define LED_IR_FRONT_R      5
/** Channel used by battery voltage LED. */
#define LED_VBAT            6

/**
 * Initialise LED controller to work.
 */
void led_init(void);

/**
 * Turn on led on a given channel.
 *
 * @param channel           LED channel.
 */
void led_on(int32_t channel);

/**
 * Turn off led on a given channel.
 *
 * @param channel           LED channel.
 */
void led_off(int32_t channel);

#endif /* _LED_H_ */
