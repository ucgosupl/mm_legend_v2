/*
 * file:	i2c_master.h
 * author:	GAndaLF
 * brief:	I2C master driver.
 */

#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

/**
 * Initialize I2C master module to work.
 */
void i2c_master_init(void);

/**
 * Write data to I2C slave device.
 *
 * @param data                  Data to be written.
 * @param slave_addr            I2C address of the slave device.
 * @param n_bytes               Number of bytes to be written.
 *
 * @return                      Error code.
 */
int32_t i2c_master_write(uint8_t *data, uint8_t slave_addr, int32_t n_bytes);

/**
 * Read data from I2C slave device.
 *
 * To read data from I2C sensor, read register should be transmitted, then I2C
 * transmission is restarted in read mode and data beggining from given register
 * address are passed to the master. Slave register should be passed on first
 * position in data buffer.
 *
 * @param data                  Slave register value on input, data read on output.
 * @param slave_addr            I2C address of the slave device.
 * @param n_bytes               Number of bytes to be read.
 *
 * @return                      Error code.
 */
int32_t i2c_master_read(uint8_t *data, uint8_t slave_addr, int32_t n_bytes);

#endif /* _I2C_MASTER_H_ */
