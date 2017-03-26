/*
 * file:    priority.h
 * author:  GAndaLF
 * brief:   Priorities and stack size definitions.
 */

#ifndef PRIORITY_H
#define PRIORITY_H

/**
 * @defgroup utils_priority
 *
 * @{
 */

/** Diagnostic task stacksize */
#define DIAG_STACKSIZE              (configMINIMAL_STACK_SIZE * 2)
/** Diagnostic task priority */
#define DIAG_PRIORITY               (tskIDLE_PRIORITY + 5)

/**
 * @}
 */

#endif /* PRIORITY_H */
