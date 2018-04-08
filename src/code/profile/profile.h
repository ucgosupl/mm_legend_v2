/*
 * file:	profile.h
 * author:	GAndaLF
 * brief:	Movement trajectory profile.
 */

#ifndef _PROFILE_H_
#define _PROFILE_H_

/**
 * Issue turn left during search run.
 */
void profile_search_turn_left(void);

/**
 * Issue turn right during search run.
 */
void profile_search_turn_right(void);

/**
 * Issue turn around during search run.
 */
void profile_search_turn_around(void);

/**
 * Issue move forward one cell during search run.
 */
void profile_search_move_forward(void);

//todo: what if command issued when in speed run?

/**
 * Check if last search run command is completed.
 */
bool profile_search_is_completed(void);

#endif /* _PROFILE_H_ */
