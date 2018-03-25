/*
 * file:	wall.h
 * author:	GAndaLF
 * brief:	Wall detection task.
 */

#ifndef _WALL_SENSOR_H_
#define _WALL_SENSOR_H_

/** Wall distance value indicating sensor error. */
#define WALL_SENSOR_ERROR           0xFFFFFFFF

/** Wall distance value indicating that wall is not in visible range (180mm). */
#define WALL_NOT_FOUND              0xFF

/** Wall distance value indicating that wall is very close to the robot (less than 30 mm). */
#define WALL_TOO_CLOSE              0x00

/** Wall sensor ids. */
enum
{
    WALL_SENSOR_FRONT_R,
    WALL_SENSOR_SIDE_L,
    WALL_SENSOR_DIAG_R,
    WALL_SENSOR_FRONT_L,
    WALL_SENSOR_SIDE_R,
    WALL_SENSOR_DIAG_L,
    WALL_SENSOR_CNT,
};

/**
 * Wall detection module init.
 */
void wall_sensor_init(void);

/**
 * Get last measured distance from sensor specified by sensor_id.
 *
 * @param sensor_id     ID of sensor to be read.
 *
 * @return              Last measured value.
 */
int32_t wall_sensor_dist_mm_get(int32_t sensor_id);

/**
 * Last measured distance from side left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_side_l_dist_mm_get(void);

/**
 * Last measured distance from side right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_side_r_dist_mm_get(void);

/**
 * Last measured distance from diagonal left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_diag_l_dist_mm_get(void);

/**
 * Last measured distance from diagonal right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_diag_r_dist_mm_get(void);

/**
 * Last measured distance from front left sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_front_l_dist_mm_get(void);

/**
 * Last measured distance from front right sensor to wall.
 *
 * @return          Distance to wall in mm.
 */
int32_t wall_sensor_front_r_dist_mm_get(void);

#endif /* _WALL_SENSOR_H_ */
