/*
 * file:	search.h
 * author:	GAndaLF
 * brief:	Search module public API.
 */

#ifndef _SEARCH_H_
#define _SEARCH_H_

/**
 * Initialize search run module.
 */
void search_init(void);

/**
 * Trigger single pass of search run state machine.
 *
 * State machine controls recalculating paths in the maze and feeding trajectory
 * profile with actions.
 */
void search_state_machine(void);

/**
 * Check if search run is finished and speed run could be started.
 *
 * @return                  True if search run finished, false otherwise.
 */
bool search_is_finished(void);

#endif /* _SEARCH_H_ */
