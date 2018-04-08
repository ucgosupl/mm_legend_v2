/*
 * file:	solver.h
 * author:	GAndaLF
 * brief:	Module finding path for labirynth map.
 */

#ifndef _SOLVER_H_
#define _SOLVER_H_

/**
 * Initialize solver module to work.
 */
void solver_init(void);

/**
 * Calculate paths to the center of the maze.
 */
void solver_calc_path_to_center(void);

/**
 * Calculate paths to the start of the maze.
 */
void solver_calc_path_to_start(void);

/**
 * Get calculated cell value.
 *
 * @param cell_id           Cell id.
 *
 * @return                  Callculated floodfill value for this cell.
 */
uint32_t solver_cell_val_get(int32_t cell_id);

/**
 * Get next cell that should be visited from current cell.
 *
 * @param cell_id           Current cell id.
 *
 * @return                  Next cell that should be visited.
 */
int32_t solver_cell_id_next_get(int32_t cell_id);

#endif /* _SOLVER_H_ */
