/*
 * file:	map_validate.c
 * author:	GAndaLF
 * brief:	Validate map update before adding.
 */

#include "platform_specific.h"
#include <string.h>

#include "map.h"
#include "map_internal.h"

struct detection_cnts
{
    int32_t present;
    int32_t absent;
};

struct wall_detection_cnts
{
    struct detection_cnts left;
    struct detection_cnts right;
    struct detection_cnts top;
    struct detection_cnts bottom;
};

static struct wall_detection_cnts map_detection_array[MAP_SIZE];

static bool update_absent_cnt_return_should_update(struct detection_cnts *cnts);
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
