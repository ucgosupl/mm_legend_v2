/*
 * file:    lsm6ds33.h
 * author:  GAndaLF
 * brief:   Defines for LSM6DS33 digital 3-axis accelerometer and gyroscope.
 */

#ifndef LSM6DS33_H_
#define LSM6DS33_H_

#define LSM6DS33_FUNC_CFG_ACCESS    0x01

#define LSM6DS33_FIFO_CTRL1         0x06
#define LSM6DS33_FIFO_CTRL2         0x07
#define LSM6DS33_FIFO_CTRL3         0x08
#define LSM6DS33_FIFO_CTRL4         0x09
#define LSM6DS33_FIFO_CTRL5         0x0A

#define LSM6DS33_ORIENT_CFG_G       0x0B

#define LSM6DS33_INT1_CTRL          0x0D
#define LSM6DS33_INT2_CTRL          0x0E

#define LSM6DS33_WHO_AM_I           0x0F

#define LSM6DS33_CTRL1_XL           0x10
#define LSM6DS33_CTRL2_G            0x11
#define LSM6DS33_CTRL3_C            0x12
#define LSM6DS33_CTRL4_C            0x13
#define LSM6DS33_CTRL5_C            0x14
#define LSM6DS33_CTRL6_C            0x15
#define LSM6DS33_CTRL7_G            0x16
#define LSM6DS33_CTRL8_XL           0x17
#define LSM6DS33_CTRL9_XL           0x18
#define LSM6DS33_CTRL10_C           0x19

#define LSM6DS33_WAKE_UP_SRC        0x1B
#define LSM6DS33_TAP_SRC            0x1C
#define LSM6DS33_D6D_SRC            0x1D
#define LSM6DS33_STATUS_REG         0x1E

#define LSM6DS33_OUT_TEMP_L         0x20
#define LSM6DS33_OUT_TEMP_H         0x21

#define LSM6DS33_OUTX_L_G           0x22
#define LSM6DS33_OUTX_H_G           0x23
#define LSM6DS33_OUTY_L_G           0x24
#define LSM6DS33_OUTY_H_G           0x25
#define LSM6DS33_OUTZ_L_G           0x26
#define LSM6DS33_OUTZ_H_G           0x27

#define LSM6DS33_OUTX_L_XL          0x28
#define LSM6DS33_OUTX_H_XL          0x29
#define LSM6DS33_OUTY_L_XL          0x2A
#define LSM6DS33_OUTY_H_XL          0x2B
#define LSM6DS33_OUTZ_L_XL          0x2C
#define LSM6DS33_OUTZ_H_XL          0x2D

#define LSM6DS33_FIFO_STATUS1       0x3A
#define LSM6DS33_FIFO_STATUS2       0x3B
#define LSM6DS33_FIFO_STATUS3       0x3C
#define LSM6DS33_FIFO_STATUS4       0x3D

#define LSM6DS33_FIFO_DATA_OUT_L    0x3E
#define LSM6DS33_FIFO_DATA_OUT_H    0x3F

#define LSM6DS33_TIMESTAMP0_REG     0x40
#define LSM6DS33_TIMESTAMP1_REG     0x41
#define LSM6DS33_TIMESTAMP2_REG     0x42

#define LSM6DS33_STEP_TIMESTAMP_L   0x49
#define LSM6DS33_STEP_TIMESTAMP_H   0x4A

#define LSM6DS33_STEP_COUNTER_L     0x4B
#define LSM6DS33_STEP_COUNTER_H     0x4C

#define LSM6DS33_FUNC_SRC           0x53

#define LSM6DS33_TAP_CFG            0x58
#define LSM6DS33_TAP_THS_6D         0x59
#define LSM6DS33_INT_DUR2           0x5A
#define LSM6DS33_WAKE_UP_THS        0x5B
#define LSM6DS33_WAKE_UP_DUR        0x5C
#define LSM6DS33_FREE_FALL          0x5D
#define LSM6DS33_MD1_CFG            0x5E
#define LSM6DS33_MD2_CFG            0x5F

#endif /* LSM6DS33_H_ */
