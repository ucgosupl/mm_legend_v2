/*
 * file:	map_internal.h
 * author:	GAndaLF
 * brief:	Functions for use internally in map module - not for public API.
 */

#ifndef _MAP_INTERNAL_H_
#define _MAP_INTERNAL_H_

#define MAP_DETECTION_THRESHOLD         3

void map_validate_init(void);
void map_validate_wall_left(int32_t cell_id, map_wall_state_t wall_state);
void map_validate_wall_right(int32_t cell_id, map_wall_state_t wall_state);
void map_validate_wall_top(int32_t cell_id, map_wall_state_t wall_state);
void map_validate_wall_bottom(int32_t cell_id, map_wall_state_t wall_state);

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

#endif /* _MAP_INTERNAL_H_ */
