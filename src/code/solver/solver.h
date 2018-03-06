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
 * Calculate paths in the maze.
 */
void solver_path_calc(void);

/**
 * Get calculated cell value.
 *
 * @param cell_id           Cell id.
 *
 * @return                  Callculated floodfill value for this cell.
 */
uint32_t solver_cell_val_get(int32_t cell_id);

#endif /* _SOLVER_H_ */
