/*
 * file:	hbridge.h
 * author:	GAndaLF
 * brief:	H-bridge for motor control module.
 */

#ifndef _HBRIDGE_H_
#define _HBRIDGE_H_

/**
 * Initialize H-bridge to work.
 *
 * Initialize all required GPIOs and Timers.
 */
void hbridge_init(void);

/**
 * Set speed for left motor.
 *
 * @param speed         Speed in percent from -100 to 100.
 *
 * @return              Error code.
 */
uint32_t hbridge_left_speed_set(int32_t speed);

/**
 * Set speed for right motor.
 *
 * @param speed         Speed in percent from -100 to 100.
 *
 * @return              Error code.
 */
uint32_t hbridge_right_speed_set(int32_t speed);

#endif /* _HBRIDGE_H_ */
