/*
 * File:    core_init.h
 * Author:  GAndaLF
 * Brief:   Core initialization.
 */

#ifndef _CORE_INIT_H_
#define _CORE_INIT_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup hw_core
 * @{
 */

/**
 * @brief Core initialization.
 *
 * This function configures clocks, FPU and other core functions.
 */
void core_init(void);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CORE_INIT_H_ */
