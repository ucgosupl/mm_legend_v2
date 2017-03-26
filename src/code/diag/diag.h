/*
 * file:    diag.h
 * author:  GAndaLF
 * brief:   Header file for diagnostic task.
 */

#ifndef _DIAG_H_
#define _DIAG_H_

/**
 * @defgroup code_diag
 *
 * @{
 */

/**
 * @brief Diagnostic task initialization.
 *
 * Diagnostic task is responsible for starting any other task and perform
 * cyclic checks.
 */
void diag_task_init(void);

/**
 * @}
 */

#endif /* _DIAG_H_ */
