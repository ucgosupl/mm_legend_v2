/*
 * file:	search_state_machine.c
 * author:	GAndaLF
 * brief:	State machine controlling search run.
 */

#include "platform_specific.h"

#include "solver/solver.h"
#include "profile/profile.h"

#include "search.h"
#include "search_internal.h"

/** Parameters needed for search run state machine. */
struct search_params
{
    search_state_t state;       /**! Current state. */
    int32_t cell_id_current;    /**! Current cell id. */
    int32_t cell_id_next;       /**! Cell id to be reached next. */
    bool is_solver_center;      /**! Is solver finds path to the center. */
};

/** State machine parameters. */
static struct search_params search_params;

/**
 * Currently used solver calculate path function.
 *
 * During search run two calculate path functions are used - to center and to start.
 * They are switched during search run when start cell / center cell reached.
 * Function calls current calculate path function.
 */
static void calc_path_wrapper(void);

/**
 * Handle state machine get next move case.
 *
 * @return                  State machine state.
 */
static search_state_t handle_state_get_next(void);

/**
 * Generate new state for robot next move obtained.
 *
 * @param next_move         Robot next move.
 *
 * @return                  State machine state.
 */
static search_state_t handle_next_move(search_move_t next_move);

void search_init(void)
{
    search_params.state = SEARCH_STATE_SOLVE;
    search_params.cell_id_current = 0;
    search_params.is_solver_center = true;
}

void search_state_machine(void)
{
    switch (search_params.state)
    {
    case SEARCH_STATE_SOLVE:
        calc_path_wrapper();
        search_params.state = SEARCH_STATE_GET_NEXT;
        /* Fallthrough */
    case SEARCH_STATE_GET_NEXT:
        search_params.state = handle_state_get_next();
        break;
    case SEARCH_STATE_TURNING_LEFT:
    case SEARCH_STATE_TURNING_RIGHT:
    case SEARCH_STATE_TURNING_AROUND:
        if (true == profile_search_is_completed())
        {
            profile_search_move_forward();
            search_params.state = SEARCH_STATE_MOVING_FORWARD;
        }
        break;
    case SEARCH_STATE_MOVING_FORWARD:
        if (true == profile_search_is_completed())
        {
            search_params.cell_id_current = search_params.cell_id_next;
            search_params.state = SEARCH_STATE_GET_NEXT;
        }
        break;
    case SEARCH_STATE_FINISHED:
        break;
    case SEARCH_STATE_ERROR:
        break;
    default:
        break;
    }
}

bool search_is_finished(void)
{
    return search_params.state == SEARCH_STATE_FINISHED;
}

static void calc_path_wrapper(void)
{
    if (true == search_params.is_solver_center)
    {
        solver_calc_path_to_center();
    }
    else
    {
        solver_calc_path_to_start();
    }
}

static search_state_t handle_state_get_next(void)
{
    search_move_t next_move;

    search_params.cell_id_next = solver_cell_id_next_get(search_params.cell_id_current);

    if (0 > search_params.cell_id_next)
    {
        if ((false == search_params.is_solver_center) && (true == search_is_final_path_found()))
        {
            return SEARCH_STATE_FINISHED;
        }

        search_params.is_solver_center = (search_params.is_solver_center != true);
        return SEARCH_STATE_SOLVE;
    }

    if (true == search_is_wall_blocking(search_params.cell_id_current, search_params.cell_id_next))
    {
        calc_path_wrapper();
        search_params.cell_id_next = solver_cell_id_next_get(search_params.cell_id_current);

        if (true == search_is_wall_blocking(search_params.cell_id_current, search_params.cell_id_next))
        {
            /*
             * After recalculating paths, wall should not be on the way.
             */

            //todo log error
            return SEARCH_STATE_ERROR;
        }
    }

    next_move = search_next_move_get(search_params.cell_id_current, search_params.cell_id_next);
    return handle_next_move(next_move);
}

static search_state_t handle_next_move(search_move_t next_move)
{
    switch (next_move)
    {
    case SEARCH_MOVE_TURN_LEFT:
        profile_search_turn_left();
        return SEARCH_STATE_TURNING_LEFT;
    case SEARCH_MOVE_TURN_RIGHT:
        profile_search_turn_right();
        return SEARCH_STATE_TURNING_RIGHT;
    case SEARCH_MOVE_TURN_AROUND:
        profile_search_turn_around();
        return SEARCH_STATE_TURNING_AROUND;
    case SEARCH_MOVE_FORWARD:
        profile_search_move_forward();
        return SEARCH_STATE_MOVING_FORWARD;
    default:
        //todo: log error, handle error
        return SEARCH_STATE_ERROR;
    }
}

#if UNIT_TEST == 1

/*
 * Functions for obtaining private fields in unit tests.
 */

search_state_t search_state_get(void)
{
    return search_params.state;
}

void search_state_set(search_state_t val)
{
    search_params.state = val;
}

int32_t search_cell_id_current_get(void)
{
    return search_params.cell_id_current;
}

void search_cell_id_current_set(int32_t val)
{
    search_params.cell_id_current = val;
}

int32_t search_cell_id_next_get(void)
{
    return search_params.cell_id_next;
}

void search_cell_id_next_set(int32_t val)
{
    search_params.cell_id_next = val;
}

bool search_is_solver_center_get(void)
{
    return search_params.is_solver_center;
}

void search_is_solver_center_set(bool val)
{
    search_params.is_solver_center = val;
}

#endif
