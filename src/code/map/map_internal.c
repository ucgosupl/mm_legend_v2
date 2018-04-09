/*
 * file:	map_internal.c
 * author:	GAndaLF
 * brief:	Functions used internally by map module.
 */

#include "platform_specific.h"

#include "map.h"
#include "map_internal.h"

int32_t map_cell_adjacent_to_wall_left_get(int32_t cell_id)
{
    if (0 == (cell_id % MAP_WIDTH))
    {
        return -1;
    }

    return cell_id - 1;
}

int32_t map_cell_adjacent_to_wall_right_get(int32_t cell_id)
{
    if ((MAP_WIDTH - 1) == (cell_id % MAP_WIDTH))
    {
        return -1;
    }

    return cell_id + 1;
}

int32_t map_cell_adjacent_to_wall_top_get(int32_t cell_id)
{
    if (cell_id >= MAP_SIZE - MAP_WIDTH)
    {
        return -1;
    }

    return cell_id + MAP_WIDTH;
}

int32_t map_cell_adjacent_to_wall_bottom_get(int32_t cell_id)
{
    if (cell_id < MAP_WIDTH)
    {
        return -1;
    }

    return cell_id - MAP_WIDTH;
}
