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

#endif /* _MAP_INTERNAL_H_ */
