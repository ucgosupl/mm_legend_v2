/*
 * file:	map.h
 * author:	GAndaLF
 * brief:	Labirynth map layout manager.
 */

#ifndef _MAP_H_
#define _MAP_H_

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

/**
 * Initialize labirynth map module to work.
 */
void map_init(void);

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

/**
 * Set left wall for a cell with a given id to absent.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_left_no_wall(int32_t cell_id);

/**
 * Set right wall for a cell with a given id to absent.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_right_no_wall(int32_t cell_id);

/**
 * Set top wall for a cell with a given id to absent.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_top_no_wall(int32_t cell_id);

/**
 * Set top wall for a cell with a given id to absent.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_bottom_no_wall(int32_t cell_id);

/**
 * Set left wall for a cell with a given id to present.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_left_wall(int32_t cell_id);

/**
 * Set right wall for a cell with a given id to present.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_right_wall(int32_t cell_id);

/**
 * Set top wall for a cell with a given id to present.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_top_wall(int32_t cell_id);

/**
 * Set bottom wall for a cell with a given id to present.
 *
 * @param cell_id           Cell id to be updated.
 */
void map_add_bottom_wall(int32_t cell_id);

#endif /* _MAP_H_ */
