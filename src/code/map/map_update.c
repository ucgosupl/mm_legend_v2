/*
 * file:	map_update.c
 * author:	GAndaLF
 * brief:	Update maze map with new wall information.
 */

#include "platform_specific.h"

#include "map.h"

PRIVATE int32_t calculate_cell(int32_t x, int32_t y);

void map_update(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state)
{

}

PRIVATE int32_t calculate_cell(int32_t x, int32_t y)
{
    int32_t cell_x;
    int32_t cell_y;

    if (x >= MAP_WIDTH * MAP_CELL_WIDTH_MM)
    {
        return -1;
    }

    if (y >= MAP_WIDTH * MAP_CELL_WIDTH_MM)
    {
        return -1;
    }

    cell_x = x / MAP_CELL_WIDTH_MM;
    cell_y = y / MAP_CELL_WIDTH_MM;

    return cell_x + MAP_WIDTH * cell_y;
}
