/*
 * file:	pid.h
 * author:	GAndaLF
 * brief:	PID controller.
 */

#ifndef _PID_H_
#define _PID_H_

/** Structure contining PID controller parameters. */
struct pid_params
{
    float p;            /** Proportional gain. */
    float i;            /** Integral gain. */
    float d;            /** Derivative gain. */
    float err_sum;      /** Sum of errors from all iterations. */
    float y_last;       /** Last output value. */
    float u_last;       /** Control signal in last iteration. */
};

/** Object containing PID controller internal parameters. */
typedef struct pid_params * pid_params_t;

/**
 * Create PID controller object with given parameters.
 *
 * @param pid           PID object to be initialized.
 * @param p             Proportional gain.
 * @param i             Integral gain.
 * @param d             Derivative gain.
 *
 * @return              Error code.
 */
int32_t pid_init(pid_params_t pid, float p, float i, float d);

/**
 * Calculate single iteration of PID controller.
 *
 * @param pid           PID controller object.
 * @param setval        Expected value.
 * @param output        Feedback output value.
 *
 * @return              Calculated control value.
 */
float pid_iter(pid_params_t pid, float setval, float output);

#endif /* _PID_H_ */
