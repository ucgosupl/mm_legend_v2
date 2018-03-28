/*
 * file:	map_validate.c
 * author:	GAndaLF
 * brief:	Validate map update before adding.
 */

#include "platform_specific.h"
#include <string.h>

#include "map.h"
#include "map_internal.h"

struct wall_detection_cnts
{
    int32_t left;
    int32_t right;
    int32_t top;
    int32_t bottom;
};

static struct wall_detection_cnts map_detection_array[MAP_SIZE];

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

    map_detection_array[cell_id].left++;
    if (map_detection_array[cell_id].left >= MAP_DETECTION_THRESHOLD)
    {
        map_add_left_wall(cell_id);
        map_detection_array[cell_id].left = MAP_DETECTION_THRESHOLD;
    }
}

void map_validate_wall_right(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_right_get(cell_id))
    {
        return;
    }

    map_detection_array[cell_id].right++;
    if (map_detection_array[cell_id].right >= MAP_DETECTION_THRESHOLD)
    {
        map_add_right_wall(cell_id);
        map_detection_array[cell_id].right = MAP_DETECTION_THRESHOLD;
    }
}

void map_validate_wall_top(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_top_get(cell_id))
    {
        return;
    }

    map_detection_array[cell_id].top++;
    if (map_detection_array[cell_id].top >= MAP_DETECTION_THRESHOLD)
    {
        map_add_top_wall(cell_id);
        map_detection_array[cell_id].top = MAP_DETECTION_THRESHOLD;
    }
}

void map_validate_wall_bottom(int32_t cell_id, map_wall_state_t wall_state)
{
    if (MAP_WALL_UNKNOWN != map_wall_bottom_get(cell_id))
    {
        return;
    }

    map_detection_array[cell_id].bottom++;
    if (map_detection_array[cell_id].bottom >= MAP_DETECTION_THRESHOLD)
    {
        map_add_bottom_wall(cell_id);
        map_detection_array[cell_id].bottom = MAP_DETECTION_THRESHOLD;
    }
}
