/*
 * file:	map_update.c
 * author:	GAndaLF
 * brief:	Update maze map with new wall information.
 */

#include "platform_specific.h"
#include <math.h>

#include "map.h"

#define WALL_PRESENT_THRESHOLD           20.0f
#define CORNER_PRESENT_THRESHOLD        30.0f

PRIVATE int32_t calculate_cell(int32_t cell_x, int32_t cell_y);
static int32_t calcluate_cell_xy(float xy);
static bool is_wall_left_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);
static bool is_wall_bottom_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);
static bool is_wall_right_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);
static bool is_wall_top_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);
static float wall_front_min(int32_t cell);
static float wall_front_max(int32_t cell);
static float wall_side_min(int32_t cell);
static float wall_side_max(int32_t cell);

void map_update(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state)
{
    int32_t cell_id;
    int32_t cell_x;
    int32_t cell_y;

    cell_x = calcluate_cell_xy(sensor_pos->x);
    cell_y = calcluate_cell_xy(sensor_pos->y);
    cell_id = calculate_cell(cell_x, cell_y);

    //todo: what to do when error - cell_xy < 0?

    if (is_wall_left_present(cell_x, cell_y, wall_pos) == true)
    {
        map_add_left_wall(cell_id);
    }
    else if (is_wall_bottom_present(cell_x, cell_y, wall_pos) == true)
    {
        map_add_bottom_wall(cell_id);
    }
    else if (is_wall_right_present(cell_x, cell_y, wall_pos) == true)
    {
        map_add_right_wall(cell_id);
    }
    else if (is_wall_top_present(cell_x, cell_y, wall_pos) == true)
    {
        map_add_top_wall(cell_id);
    }
    else
    {
        /* Wall cannot be added - constraints not meet. */
    }
}

static int32_t calcluate_cell_xy(float xy)
{
    if (xy >= MAP_WIDTH * MAP_CELL_WIDTH_MM)
    {
        return -1;
    }

    return xy / MAP_CELL_WIDTH_MM;
}

PRIVATE int32_t calculate_cell(int32_t cell_x, int32_t cell_y)
{
    return cell_x + MAP_WIDTH * cell_y;
}

static bool is_wall_left_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos)
{
    float l_x_min = wall_front_min(cell_x);
    float l_x_max = wall_front_max(cell_x);
    float l_y_min = wall_side_min(cell_y);
    float l_y_max = wall_side_max(cell_y);

    if ((l_x_min < wall_pos->x) && (l_x_max > wall_pos->x))
    {
        if ((l_y_min < wall_pos->y) && (l_y_max > wall_pos->y))
        {
            return true;
        }
    }

    return false;
}

static bool is_wall_bottom_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos)
{
    float b_x_min = wall_side_min(cell_x);
    float b_x_max = wall_side_max(cell_x);
    float b_y_min = wall_front_min(cell_y);
    float b_y_max = wall_front_max(cell_y);

    if ((b_x_min < wall_pos->x) && (b_x_max > wall_pos->x))
    {
        if ((b_y_min < wall_pos->y) && (b_y_max > wall_pos->y))
        {
            return true;
        }
    }

    return false;
}

static bool is_wall_right_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos)
{
    float r_x_min = wall_front_min(cell_x + 1);
    float r_x_max = wall_front_max(cell_x + 1);
    float r_y_min = wall_side_min(cell_y);
    float r_y_max = wall_side_max(cell_y);

    if ((r_x_min < wall_pos->x) && (r_x_max > wall_pos->x))
    {
        if ((r_y_min < wall_pos->y) && (r_y_max > wall_pos->y))
        {
            return true;
        }
    }

    return false;
}

static bool is_wall_top_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos)
{
    float t_x_min = wall_side_min(cell_x);
    float t_x_max = wall_side_max(cell_x);
    float t_y_min = wall_front_min(cell_y + 1);
    float t_y_max = wall_front_max(cell_y + 1);

    if ((t_x_min < wall_pos->x) && (t_x_max > wall_pos->x))
    {
        if ((t_y_min < wall_pos->y) && (t_y_max > wall_pos->y))
        {
            return true;
        }
    }

    return false;
}

static float wall_front_min(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM - WALL_PRESENT_THRESHOLD;
}

static float wall_front_max(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM + WALL_PRESENT_THRESHOLD;
}

static float wall_side_min(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM + CORNER_PRESENT_THRESHOLD;
}

static float wall_side_max(int32_t cell)
{
    return (cell + 1) * MAP_CELL_WIDTH_MM - CORNER_PRESENT_THRESHOLD;
}
