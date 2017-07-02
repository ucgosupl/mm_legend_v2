/*
 * file:	console.c
 * author:	GAndaLF
 * brief:   Debug console.
 */

#include "platform_specific.h"
#include "priority.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "usart/usart.h"
#include "logger/logger.h"
#include "hbridge/hbridge.h"

#include "console.h"

#define SPEED1  20
#define SPEED2  40
#define SPEED3  60

static void console_task(void *params);

void console_task_init(void)
{
    hbridge_init();
    usart_init();

    rtos_task_create(console_task, "console", CONSOLE_STACKSIZE, CONSOLE_PRIORITY);
}

static void console_task(void *params)
{
    (void) params;

    uint8_t rx_byte;
    int32_t speed;

    speed = SPEED1;

    while (1)
    {
        if (0 != usart_is_rx_rdy())
        {
            rx_byte = usart_read_byte();

            switch (rx_byte)
            {
            case 'w':
                hbridge_left_speed_set(speed);
                hbridge_right_speed_set(speed);
                break;
            case 's':
                hbridge_left_speed_set(-speed);
                hbridge_right_speed_set(-speed);
                break;
            case 'a':
                hbridge_left_speed_set(-speed);
                hbridge_right_speed_set(speed);
                break;
            case 'd':
                hbridge_left_speed_set(speed);
                hbridge_right_speed_set(-speed);
                break;
            case ' ':
                hbridge_left_speed_set(0);
                hbridge_right_speed_set(0);
                break;
            case '1':
                speed = SPEED1;
                break;
            case '2':
                speed = SPEED2;
                break;
            case '3':
                speed = SPEED3;
                break;
            default:
                break;
            }
        }

        rtos_delay(10);
    }
    //wait for input from debug usart
    //check if input matches predefined command
    //execute command
}
