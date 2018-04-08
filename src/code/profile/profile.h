/*
 * file:	profile.h
 * author:	GAndaLF
 * brief:	Movement trajectory profile.
 */

#ifndef _PROFILE_H_
#define _PROFILE_H_

void profile_search_turn_left(void);
void profile_search_turn_right(void);
void profile_search_turn_around(void);
void profile_search_move_forward(void);

bool profile_search_is_completed(void);

#endif /* _PROFILE_H_ */
