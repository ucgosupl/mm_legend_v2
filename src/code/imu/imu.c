/*
 * file:	imu.c
 * author:	GAndaLF
 * brief:   Task reading data from IMU sensor.
 */

#include "platform_specific.h"

#include "i2c_master/i2c_master.h"

#include "lsm6ds33.h"
#include "imu.h"

/** I2C address of the gyroscope */
#define GYRO_ADDR               0b1101011
/** I2C address of the accelerometer */
#define ACC_ADDR                0b1101011

/** Range of the gyroscope in degrees per second (dps) */
#define GYRO_RANGE_DPS          2000.0f
/** Range of the accelerometer in g */
#define ACC_RANGE_G             2.0f
/** Range of the magnetometer in gauss */
#define MAG_RANGE_GAUSS         1.3f

/** Value of the gravitational acceleration */
#define CONST_G                 9.80665f

/**
 * Data read from the sensor.
 */
struct sensor_data {
    int16_t x;          /**< Value in X axis */
    int16_t y;          /**< Value in Y axis */
    int16_t z;          /**< Value in Z axis */
};

/**
 * Data read from the gyroscope.
 */
static struct sensor_data gyro_data;

/**
 * Data read from the accelerometer.
 */
static struct sensor_data acc_data;

/**
 * Data read from the magnetometer.
 */
static struct sensor_data mag_data;

/**
 * IMU sensor task handler.
 *
 * @param params        Task parameters - unused.
 */
static void imu_task(void *params);

/**
 * Write data to the single register of the I2C sensor.
 *
 * @param slave_addr            I2C slave address.
 * @param reg_addr              Register address.
 * @param val                   Value to write to the register.
 */
static void write_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t val);

/**
 * Read data from the single register of the I2C sensor.
 *
 * @param slave_addr            I2C slave address.
 * @param reg_addr              Register address.
 *
 * @return                      Data read from the device.
 */
static int16_t read_reg(uint8_t slave_addr, uint8_t reg_addr);

/**
 * Convert digital data read from gyroscope to the physical value.
 *
 * @param val                   Value read from the gyroscope.
 *
 * @return                      Value converted to the physical representation.
 */
static float gyro_scale(int16_t val);

/**
 * Convert digital data read from accelerometer to the physical value.
 *
 * @param val                   Value read from the accelerometer.
 *
 * @return                      Value converted to the physical representation.
 */
static float acc_scale(int16_t val);

/**
 * Convert digital data read from magnetometer to the physical value.
 *
 * @param val                   Value read from the magnetometer.
 *
 * @return                      Value converted to the physical representation.
 */
static float mag_scale(int16_t val);

void imu_task_init(void)
{
    gyro_data.x = 0.0f;
    gyro_data.y = 0.0f;
    gyro_data.z = 0.0f;

    acc_data.x = 0.0f;
    acc_data.y = 0.0f;
    acc_data.z = 0.0f;

    mag_data.x = 0.0f;
    mag_data.y = 0.0f;
    mag_data.z = 0.0f;

    i2c_master_init();
    rtos_task_create(imu_task, "imu", IMU_STACKSIZE, IMU_PRIORITY);
}

float imu_acc_x_get(void)
{
    return acc_scale(acc_data.x);
}

float imu_acc_y_get(void)
{
    return acc_scale(acc_data.y);
}

float imu_acc_z_get(void)
{
    return acc_scale(acc_data.z);
}

float imu_gyro_x_get(void)
{
    return gyro_scale(gyro_data.x);
}

float imu_gyro_y_get(void)
{
    return gyro_scale(gyro_data.y);
}

float imu_gyro_z_get(void)
{
    return gyro_scale(gyro_data.z);
}

float imu_mag_x_get(void)
{
    return mag_scale(mag_data.x);
}

float imu_mag_y_get(void)
{
    return mag_scale(mag_data.y);
}

float imu_mag_z_get(void)
{
    return mag_scale(mag_data.z);
}

static void imu_task(void *params)
{
    tick_t ticks;

    (void) params;

    /*
     * Gyro:
     * - enable axes X, Y and Z
     * - power on
     * - sampling frequency 1666 Hz
     * - cutoff 12.5 Hz
     * - range +/- 2000dps
     */
    write_reg(GYRO_ADDR, LSM6DS33_CTRL10_C, 0x38);
    write_reg(GYRO_ADDR, LSM6DS33_CTRL2_G, 0x8C);

    /*
     * Accelerometer:
     * - enable axes X, Y and Z
     * - sampling frequency 1666 Hz
     * - range +/- 2g
     * - filter bandwith 400 Hz
     */
    write_reg(GYRO_ADDR, LSM6DS33_CTRL9_XL, 0x38);
    write_reg(ACC_ADDR, LSM6DS33_CTRL1_XL, 0x80);

    while (1) {
        ticks = rtos_tick_count_get();

        /* Read data from the gyroscope */
        gyro_data.x = read_reg(GYRO_ADDR, LSM6DS33_OUTX_L_G);
        gyro_data.y = read_reg(GYRO_ADDR, LSM6DS33_OUTY_L_G);
        gyro_data.z = read_reg(GYRO_ADDR, LSM6DS33_OUTZ_L_G);

        /* Read data from the accelerometer */
        acc_data.x = read_reg(ACC_ADDR, LSM6DS33_OUTX_L_XL);
        acc_data.y = read_reg(ACC_ADDR, LSM6DS33_OUTY_L_XL);
        acc_data.z = read_reg(ACC_ADDR, LSM6DS33_OUTZ_L_XL);

        rtos_delay_until(&ticks, 1);
    }
}

static void write_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t val)
{
    uint8_t data[2];

    data[0] = reg_addr;
    data[1] = val;
    i2c_master_write(data, slave_addr, 2);
}

static int16_t read_reg(uint8_t slave_addr, uint8_t reg_addr)
{
    uint8_t data[2];

    data[0] = reg_addr;
    i2c_master_read(data, slave_addr, 2);

    return (int16_t)((data[1] << 8) | data[0]);
}

static float gyro_scale(int16_t val)
{
    return ((float) val / 0x8000) * GYRO_RANGE_DPS;
}

static float acc_scale(int16_t val)
{
    return ((float) val / 0x8000) * ACC_RANGE_G * CONST_G;
}

static float mag_scale(int16_t val)
{
    return ((float) val / 0x8000) * MAG_RANGE_GAUSS;
}
