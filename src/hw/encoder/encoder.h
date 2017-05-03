/*
 * file:	encoder.h
 * author:	GAndaLF
 * brief:	Motor encoders driver.
 */

#ifndef _ENCODER_H_
#define _ENCODER_H_

/**
 * Initialize motor encoders to work.
 */
void encoder_init(void);

/**
 * Read left motor encoder increment from last read.
 *
 * @return              Increment value from last read.
 */
int32_t encoder_left_read(void);

/**
 * Read right motor encoder increment from last read.
 *
 * @return              Increment value from last read.
 */
int32_t encoder_right_read(void);

#endif /* _ENCODER_H_ */
