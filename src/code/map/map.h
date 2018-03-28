/*
 * file:	map.h
 * author:	GAndaLF
 * brief:	Labirynth map layout manager.
 */

#ifndef _MAP_H_
#define _MAP_H_

/** Width of a single maze cell. */
#define MAP_CELL_WIDTH_MM       180

/** Labirynth map width in cells. */
#define MAP_WIDTH   16

/** Labirynth map height in cells. */
#define MAP_HEIGHT  16

/** Number of cells in the labirynth. */
#define MAP_SIZE    (MAP_WIDTH * MAP_HEIGHT)

/** Type for wall presence state. */
typedef int32_t map_wall_state_t;

enum
{
    MAP_WALL_UNKNOWN = 0,
    MAP_WALL_PRESENT = 1,
    MAP_WALL_ABSENT = 2,
    MAP_WALL_ERROR = 0xFF,
};

/** Point in robot coordinate system including orientation. */
struct coords
{
    float x;        /**< Position in X axis in millimeters. */
    float y;        /**< Position in Y axis in millimeters. */
    float alpha;    /**< Orientation in degrees. */
};

/**
 * Initialize labirynth map module to work.
 */
void map_init(void);

/**
 * Update map with new wall information.
 *
 * This function is for adding information about scanned wall. It could add information
 * about detected wall presence or absence. When wall_state indicates presence,
 * wall_pos represents detected point in the wall. When wall_state indicates absence,
 * wall_pos represents farthest point with no wall on the way from sensor.
 *
 * @param sensor_pos        Position of sensor which did this measurement.
 * @param wall_pos          Position of detected wall.
 * @param wall_state        Information if detected wall or no wall.
 */
void map_update(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state);

/**
 * Get left wall presence state for cell with a given id.
 *
 * @param cell_id           Cell id to be checked.
 *
 * @return                  Left wall presence state.
 */
map_wall_state_t map_wall_left_get(int32_t cell_id);

/**
 * Get right wall presence state for cell with a given id.
 *
 * @param cell_id           Cell id to be checked.
 *
 * @return                  Right wall presence state.
 */
map_wall_state_t map_wall_right_get(int32_t cell_id);

/**
 * Get top wall presence state for cell with a given id.
 *
 * @param cell_id           Cell id to be checked.
 *
 * @return                  Top wall presence state.
 */
map_wall_state_t map_wall_top_get(int32_t cell_id);

/**
 * Get bottom wall presence state for cell with a given id.
 *
 * @param cell_id           Cell id to be checked.
 *
 * @return                  Bottom wall presence state.
 */
map_wall_state_t map_wall_bottom_get(int32_t cell_id);

#endif /* _MAP_H_ */
