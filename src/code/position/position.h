/*
 * file:	position.h
 * author:	GAndaLF
 * brief:	Position estimation task.
 */

#ifndef _POSITION_H_
#define _POSITION_H_

/**
 * Initialize position estimation task.
 */
void position_task_init(void);

/**
 * Get current position x coordinate estimation.
 *
 * @return      X coordinate estimation.
 */
float position_x_get(void);

/**
 * Get current position y coordinate estimation.
 *
 * @return      Y coordinate estimation.
 */
float position_y_get(void);

/**
 * Get current orientation angle estimation.
 *
 * @return      Alpha orientation angle estimation.
 */
float position_alpha_get(void);

/**
 * Get current linear velocity estimation.
 *
 * @return      Linear velocity estimation.
 */
float position_v_get(void);

/**
 * Get current angular velocity estimation.
 *
 * @return      Angular velocity estimation.
 */
float position_omega_get(void);

/**
 * Get current gyroscope offset estimation.
 *
 * @return      gyroscope offset estimation.
 */
float position_bias_get(void);
#endif /* _POSITION_H_ */
