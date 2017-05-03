/*
 * file:	i2c_master.c
 * author:	GAndaLF
 * brief:	I2C master driver.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "i2c_master.h"

void i2c_master_init(void)
{

}

int32_t i2c_master_write(uint8_t *data, uint8_t slave_addr, int32_t n_bytes)
{
    (void) data;
    (void) slave_addr;
    (void) n_bytes;

    return 0;
}

int32_t i2c_master_read(uint8_t *data, uint8_t slave_addr, int32_t n_bytes)
{
    (void) data;
    (void) slave_addr;
    (void) n_bytes;

    return 0;
}
