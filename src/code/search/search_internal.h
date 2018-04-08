/*
 * file:	search_internal.h
 * author:	GAndaLF
 * brief:	Search module functions for internal use.
 */

#ifndef _SEARCH_INTERNAL_H_
#define _SEARCH_INTERNAL_H_

enum
{
    SEARCH_STATE_SOLVE,
    SEARCH_STATE_GET_NEXT,
    SEARCH_STATE_TURNING_LEFT,
    SEARCH_STATE_TURNING_RIGHT,
    SEARCH_STATE_TURNING_AROUND,
    SEARCH_STATE_MOVING_FORWARD,
    SEARCH_STATE_FINISHED,
    SEARCH_STATE_ERROR,
};

enum
{
    SEARCH_MOVE_FORWARD,
    SEARCH_MOVE_TURN_LEFT,
    SEARCH_MOVE_TURN_RIGHT,
    SEARCH_MOVE_TURN_AROUND,
};

typedef int32_t search_state_t;
typedef int32_t search_move_t;

bool search_is_wall_blocking(int32_t id_current, int32_t id_next);
search_move_t search_next_move_get(int32_t id_current, int32_t id_next);
bool search_is_final_path_found(void);

#endif /* _SEARCH_INTERNAL_H_ */
