/*
 * file:	motor.h
 * author:	GAndaLF
 * brief:	Motor control task.
 */

#ifndef _MOTOR_H_
#define _MOTOR_H_

/**
 * Initialize motor task to work.
 */
void motor_task_init(void);

/**
 * Get current velocity of the left motor.
 *
 * @return          Velocity in mm/s.
 */
float motor_vleft_get(void);

/**
 * Get current velocity of the right motor.
 *
 * @return          Velocity in mm/s.
 */
float motor_vright_get(void);

/**
 * Set expected value of linear velocity.
 *
 * @param val       Expected linear velocity.
 */
void motor_vlinear_set(float val);

/**
 * Set expected value of angular velocity.
 *
 * @param val       Expected linear velocity.
 */
void motor_vangular_set(float val);

/**
 * Emergency turn off all motors.
 */
void motor_all_off(void);

/**
 * Reset state of linear velocity PID controller.
 */
void motor_pid_linear_reset(void);

/**
 * Reset state of angular velocity PID controller.
 */
void motor_pid_angular_reset(void);

#endif /* _MOTOR_H_ */
