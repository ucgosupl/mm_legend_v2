/*
 * file:	search_internal.h
 * author:	GAndaLF
 * brief:	Search module functions for internal use.
 */

#ifndef _SEARCH_INTERNAL_H_
#define _SEARCH_INTERNAL_H_

/** Possible search state machine states. */
enum
{
    SEARCH_STATE_SOLVE,             /** Run solver. */
    SEARCH_STATE_GET_NEXT,          /** Issue next move command. */
    SEARCH_STATE_TURNING_LEFT,      /** Turning left in progress. */
    SEARCH_STATE_TURNING_RIGHT,     /** Turning right in progress. */
    SEARCH_STATE_TURNING_AROUND,    /** Turning around in progress. */
    SEARCH_STATE_MOVING_FORWARD,    /** Moving forward in progress. */
    SEARCH_STATE_FINISHED,          /** Search run finished. */
    SEARCH_STATE_ERROR,             /** State machine error. */
};

/** Possible robot move commands. */
enum
{
    SEARCH_MOVE_FORWARD,
    SEARCH_MOVE_TURN_LEFT,
    SEARCH_MOVE_TURN_RIGHT,
    SEARCH_MOVE_TURN_AROUND,
};

/** Type for storing search state machine states. */
typedef int32_t search_state_t;

/** Type for storing robot move commands available in search run. */
typedef int32_t search_move_t;

/**
 * Check if wall is blocking move to the next cell.
 *
 * If since last solver run new walls were detected, there is possiblity that
 * wall marked by unknonwn when solving is now present. If it is the case,
 * solve function must be called again and new next cell should be chosen based
 * on new solved values.
 *
 * @param id_current        Id of current cell.
 * @param id_next           Id of next cell.
 *
 * @return                  True if wall between cells, false otherwise.
 */
bool search_is_wall_blocking(int32_t id_current, int32_t id_next);

/**
 * Get robot move command needed to move from current cell to the next.
 *
 * @param id_current        Id of current cell.
 * @param id_next           Id of next cell.
 *
 * @return                  Robot move command.
 */
search_move_t search_next_move_get(int32_t id_current, int32_t id_next);

/**
 * Check if final path was found.
 *
 * Final path contains only PRESENT or ABSENT walls, no UNKNOWN. When final
 * path found, no further exploration of the labirynth is needed.
 *
 * @return                  True if found, false otherwise.
 */
bool search_is_final_path_found(void);

#endif /* _SEARCH_INTERNAL_H_ */
