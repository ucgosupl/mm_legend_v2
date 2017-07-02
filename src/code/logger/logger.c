/*
 * file:	logger.c
 * author:	GAndaLF
 * brief:	Logging data to debug USART.
 */

#include <string.h>

#include "platform_specific.h"

#include "usart/usart.h"

#include "logger.h"

/** Period of sending logged data to USART driver in milliseconds. */
#define FLUSH_INTERVAL_MS   50

/**
 * Size of a single logger buffer.
 *
 * Buffer size is calculated to store more bytes than maximum driver throughput
 * so it can be send later when new data are not received.
 */
#define LOG_BUF_SIZE    1024

/** Structure containing logger internal parameters. */
struct logger_params
{
    uint8_t *buf;       /** Pointer to buffer currently used for writing data. */
    int32_t cnt;        /** Number of bytes written to current buffer. */
    uint32_t next_buf;  /** Index of next buffer to be used for logging. */
    mutex_t mutex;      /** Mutex for protecting buffer during sending to driver. */
};

/** Logger task internal parameters. */
static struct logger_params log_params;
/**
 * Buffers used for storing logger data.
 *
 * When one buffer is sent to USART driver, second is used for storing data received
 * from the application. After predefined time interval buffer with received data
 * is passed to driver and other buffer is used for writing new data.
 */
static uint8_t bufs[2][LOG_BUF_SIZE];

/**
 * Logger task procedure.
 *
 * @param params        Parameter unused.
 */
static void logger_task(void *params);

/**
 * Switch currently used buffer.
 */
static void switch_bufs(void);

void logger_task_init(void)
{
    usart_init();

    log_params.mutex = rtos_mutex_create();
    rtos_mutex_give(log_params.mutex);

    rtos_task_create(logger_task, "logger", LOGGER_STACKSIZE, LOGGER_PRIORITY);
}

int32_t logger_write_buffer(uint8_t *buf, int32_t len)
{
    int32_t n_bytes;

    if (buf == NULL)
    {
        /* Invalid argument */
        return -EINVAL;
    }

    if (rtos_mutex_take(log_params.mutex, 10) != true)
    {
        /* Report timeout */
        return -EBUSY;
    }

    /* Calculate maximum possible number of bytes to write */
    n_bytes = (log_params.cnt + len > LOG_BUF_SIZE) ?
              (LOG_BUF_SIZE - log_params.cnt) :
              (len);

    /* Write data to the send buffer */
    memcpy(log_params.buf + log_params.cnt, buf, n_bytes);
    log_params.cnt += n_bytes;

    rtos_mutex_give(log_params.mutex);

    return n_bytes;
}

static void logger_task(void *params)
{
    (void) params;

    tick_t ticks;

    switch_bufs();

    while (true)
    {
        ticks = rtos_tick_count_get();

        if (rtos_mutex_take(log_params.mutex, 10) == true)
        {
            if (0 <= usart_send_buf(log_params.buf, log_params.cnt))
            {
                switch_bufs();
            }
            /*
             * If USART send failed - probably old data transfer not finished. When new
             * logged data arrives they will be added to current buffer. Next try to
             * flush data will be performed in the next iteration.
             */

            rtos_mutex_give(log_params.mutex);
        }

        rtos_delay_until(&ticks, FLUSH_INTERVAL_MS);
    }
}

static void switch_bufs(void)
{
    log_params.buf = bufs[log_params.next_buf];

    log_params.next_buf++;
    log_params.next_buf &= 0x00000001;
    log_params.cnt = 0;
}
