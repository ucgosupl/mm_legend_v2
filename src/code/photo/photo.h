/*
 * file:	photo.h
 * author:	GAndaLF
 * brief:	Reading voltage from phototransistors.
 */

#ifndef _PHOTO_H_
#define _PHOTO_H_

/**
 * Initialize phototransistor module to work.
 */
void photo_init(void);

/**
 * Read value of side left phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_side_l_get(void);

/**
 * Read value of side right phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_side_r_get(void);

/**
 * Read value of diagonal left phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_diag_l_get(void);

/**
 * Read value of diagonal right phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_diag_r_get(void);

/**
 * Read value of front left phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_front_l_get(void);

/**
 * Read value of front right phototransistor.
 *
 * @return          Value read.
 */
int32_t photo_front_r_get(void);

#endif /* _PHOTO_H_ */
