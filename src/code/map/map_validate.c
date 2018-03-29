/*
 * file:	map_validate.c
 * author:	GAndaLF
 * brief:	Validate map update before adding.
 */

#include "platform_specific.h"
#include <string.h>

#include "map.h"
#include "map_internal.h"

/** Structure containing wall presence/absence counters. */
struct detection_cnts
{
    int32_t present;                /**< Wall presence counter. */
    int32_t absent;                 /**< Wall absence counter. */
};

/** Counters for all walls in a single cell. */
struct wall_detection_cnts
{
    struct detection_cnts left;     /**< Counters for left wall. */
    struct detection_cnts right;    /**< Counters for right wall. */
    struct detection_cnts top;      /**< Counters for top wall. */
    struct detection_cnts bottom;   /**< Counters for bottom wall. */
};

/** Array containing wall counters for every cell. */
static struct wall_detection_cnts map_detection_array[MAP_SIZE];

/**
 * Update wall absence count and inform if wall map should be updated.
 *
 * @param cnts              Pointer to wall counters to be updated.
 *
 * @return                  True if wall map should be updated, false otherwise.
 */
static bool update_absent_cnt_return_should_update(struct detection_cnts *cnts);

/**
 * Update wall presence count and inform if wall map should be updated.
 *
 * @param cnts              Pointer to wall counters to be updated.
 *
 * @return                  True if wall map should be updated, false otherwise.
 */
static bool update_present_cnt_return_should_update(struct detection_cnts *cnts);

void map_validate_init(void)
{
    memset(map_detection_array, 0, MAP_SIZE * sizeof(struct wall_detection_cnts));
}

void map_validate_wall_left(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_left_get(cell_id))
    {
        return;
    }

    if (MAP_WALL_ABSENT == wall_state)
    {
        if (update_absent_cnt_return_should_update(&map_detection_array[cell_id].left))
        {
            map_add_left_no_wall(cell_id);
        }
    }
    else if (MAP_WALL_PRESENT == wall_state)
    {
        if (update_present_cnt_return_should_update(&map_detection_array[cell_id].left))
        {
            map_add_left_wall(cell_id);
        }
    }
    else
    {

    }
}

void map_validate_wall_right(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_right_get(cell_id))
    {
        return;
    }

    if (MAP_WALL_ABSENT == wall_state)
    {
        if (update_absent_cnt_return_should_update(&map_detection_array[cell_id].right))
        {
            map_add_right_no_wall(cell_id);
        }
    }
    else if (MAP_WALL_PRESENT == wall_state)
    {
        if (update_present_cnt_return_should_update(&map_detection_array[cell_id].right))
        {
            map_add_right_wall(cell_id);
        }
    }
    else
    {

    }
}

void map_validate_wall_top(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_top_get(cell_id))
    {
        return;
    }

    if (MAP_WALL_ABSENT == wall_state)
    {
        if (update_absent_cnt_return_should_update(&map_detection_array[cell_id].top))
        {
            map_add_top_no_wall(cell_id);
        }
    }
    else if (MAP_WALL_PRESENT == wall_state)
    {
        if (update_present_cnt_return_should_update(&map_detection_array[cell_id].top))
        {
            map_add_top_wall(cell_id);
        }
    }
    else
    {

    }
}

void map_validate_wall_bottom(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_bottom_get(cell_id))
    {
        return;
    }

    if (MAP_WALL_ABSENT == wall_state)
    {
        if (update_absent_cnt_return_should_update(&map_detection_array[cell_id].bottom))
        {
            map_add_bottom_no_wall(cell_id);
        }
    }
    else if (MAP_WALL_PRESENT == wall_state)
    {
        if (update_present_cnt_return_should_update(&map_detection_array[cell_id].bottom))
        {
            map_add_bottom_wall(cell_id);
        }
    }
    else
    {

    }
}

static bool update_absent_cnt_return_should_update(struct detection_cnts *cnts)
{
    if (0 < cnts->present)
    {
        cnts->absent = 0;
        cnts->present = 0;
        return false;
    }

    cnts->absent++;
    if (cnts->absent >= MAP_DETECTION_THRESHOLD)
    {
        cnts->absent = MAP_DETECTION_THRESHOLD;
        return true;
    }

    return false;
}

static bool update_present_cnt_return_should_update(struct detection_cnts *cnts)
{
    if (0 < cnts->absent)
    {
        cnts->absent = 0;
        cnts->present = 0;
        return false;
    }

    cnts->present++;
    if (cnts->present >= MAP_DETECTION_THRESHOLD)
    {
        cnts->present = MAP_DETECTION_THRESHOLD;
        return true;
    }

    return false;
}
