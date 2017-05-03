/*
 * file:	pid.h
 * author:	GAndaLF
 * brief:	PID controller.
 */

#ifndef _PID_H_
#define _PID_H_

/** Object containing PID controller internal parameters. */
typedef struct pid_params_s * pid_params_t;

/**
 * Create PID controller object with given parameters.
 *
 * @param p             Proportional gain.
 * @param i             Integral gain.
 * @param d             Derivative gain.
 *
 * @return          Created PID object.
 */
pid_params_t pid_create(float p, float i, float d);

/**
 * Calculate single iteration of PID controller.
 *
 * @param pid           PID controller object.
 * @param setval        Expected value.
 * @param output        Feedback output value.
 * @return
 */
float pid_iter(pid_params_t pid, float setval, float output);

#endif /* _PID_H_ */
