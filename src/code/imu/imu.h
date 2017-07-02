/*
 * file:	imu.h
 * author:	GAndaLF
 * brief:	Task reading data from IMU sensor.
 */

#ifndef _IMU_H_
#define _IMU_H_

/**
 * Initialize IMU sensor reading task to work.
 */
void imu_task_init(void);

/**
 * Get last reading of accelerometer X axis.
 *
 * @return              Accelerometer value.
 */
float imu_acc_x_get(void);

/**
 * Get last reading of accelerometer Y axis.
 *
 * @return              Accelerometer value.
 */
float imu_acc_y_get(void);

/**
 * Get last reading of accelerometer Z axis.
 *
 * @return              Accelerometer value.
 */
float imu_acc_z_get(void);

/**
 * Get last reading of gyro X axis.
 *
 * @return              Gyro value.
 */
float imu_gyro_x_get(void);

/**
 * Get last reading of gyro Y axis.
 *
 * @return              Gyro value.
 */
float imu_gyro_y_get(void);

/**
 * Get last reading of gyro Z axis.
 *
 * @return              Gyro value.
 */
float imu_gyro_z_get(void);

/**
 * Get last reading of magnetometer X axis.
 *
 * @return              Magnetometer value.
 */
float imu_mag_x_get(void);

/**
 * Get last reading of magnetometer Y axis.
 *
 * @return              Magnetometer value.
 */
float imu_mag_y_get(void);

/**
 * Get last reading of magnetometer Z axis.
 *
 * @return              Magnetometer value.
 */
float imu_mag_z_get(void);

#endif /* _IMU_H_ */
