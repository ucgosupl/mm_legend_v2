/*
 * file:	wall.h
 * author:	GAndaLF
 * brief:	Wall detection task.
 */

#ifndef _WALL_H_
#define _WALL_H_

/** Wall distance value indicating sensor error. */
#define WALL_ERROR          0xFFFFFFFF

/** Wall distance value indicating that wall is not in visible range (180mm). */
#define WALL_NOT_FOUND      0x0000FFFF

/** Wall distance value indicating that wall is very close to the robot (less than 30 mm). */
#define WALL_TOO_CLOSE      0x00000000

/**
 * Wall detection module init.
 */
void wall_init(void);

/**
 * Last measured distance from side left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_side_l_dist_mm_get(void);

/**
 * Last measured distance from side right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_side_r_dist_mm_get(void);

/**
 * Last measured distance from diagonal left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_diag_l_dist_mm_get(void);

/**
 * Last measured distance from diagonal right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_diag_r_dist_mm_get(void);

/**
 * Last measured distance from front left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_front_l_dist_mm_get(void);

/**
 * Last measured distance from front right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_front_r_dist_mm_get(void);

#endif /* _WALL_H_ */
