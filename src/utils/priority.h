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

/** Console task stacksize */
#define CONSOLE_STACKSIZE           (configMINIMAL_STACK_SIZE)
/** Console task priority */
#define CONSOLE_PRIORITY            (tskIDLE_PRIORITY + 5)

/** Diagnostic task stacksize */
#define DIAG_STACKSIZE              (configMINIMAL_STACK_SIZE * 2)
/** Diagnostic task priority */
#define DIAG_PRIORITY               (tskIDLE_PRIORITY + 6)

/** IMU sensor task stacksize */
#define IMU_STACKSIZE               (configMINIMAL_STACK_SIZE * 2)
/** IMU sensor task priority */
#define IMU_PRIORITY                (tskIDLE_PRIORITY + 4)

/** Logger task stacksize */
#define LOGGER_STACKSIZE           (configMINIMAL_STACK_SIZE)
/** Logger task priority */
#define LOGGER_PRIORITY            (tskIDLE_PRIORITY + 4)

/** Motor task stacksize */
#define MOTOR_STACKSIZE           (configMINIMAL_STACK_SIZE * 2)
/** Motor task priority */
#define MOTOR_PRIORITY            (tskIDLE_PRIORITY + 3)

/** Logger USART HW priority */
#define LOGGER_USART_PRIORITY           10
/** DMA on I2C RX HW priority */
#define DMA_I2C_RX_PRIORITY             9
/** DMA on I2C TX HW priority */
#define DMA_I2C_TX_PRIORITY             9
/** I2C1 Event HW priority */
#define I2C1_EV_PRIORITY                8

/**
 * @}
 */

#endif /* PRIORITY_H */
