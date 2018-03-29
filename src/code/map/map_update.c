/*
 * file:	map_update.c
 * author:	GAndaLF
 * brief:	Update maze map with new wall information.
 */

#include "platform_specific.h"
#include <math.h>

#include "map.h"
#include "map_internal.h"

/** Distance from cell edge where wall is detected. */
#define WALL_THRESHOLD                  20.0f

/** Distance from cell corner where wall is detected. */
#define CORNER_THRESHOLD                30.0f

/**
 * Add to map information about present wall.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param wall_pos                      Detected wall coordinates.
 */
static void wall_present_add(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);

/**
 * Add to map information about absent wall.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param sensor_pos                    Sensor coordinates.
 * @param wall_pos                      Farthest point with no wall coordinates.
 */
static void wall_absent_add(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos);

/**
 * Check if detected present wall is left for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param wall_pos                      Detected wall coordinates.
 *
 * @return                              True if left wall detected, false otherwise.
 */
static bool is_wall_left_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);

/**
 * Check if detected present wall is bottom for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param wall_pos                      Detected wall coordinates.
 *
 * @return                              True if bottom wall detected, false otherwise.
 */
static bool is_wall_bottom_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);

/**
 * Check if detected present wall is right for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param wall_pos                      Detected wall coordinates.
 *
 * @return                              True if right wall detected, false otherwise.
 */
static bool is_wall_right_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);

/**
 * Check if detected present wall is top for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param wall_pos                      Detected wall coordinates.
 *
 * @return                              True if top wall detected, false otherwise.
 */
static bool is_wall_top_present(int32_t cell_x, int32_t cell_y, struct coords *wall_pos);

/**
 * Check if absent wall is left for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param sensor_pos                    Sensor coordinates.
 * @param wall_pos                      Farthest point with no wall coordinates.
 *
 * @return                              True if left wall absence detected, false otherwise.
 */
static bool is_wall_left_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos);

/**
 * Check if absent wall is bottom for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param sensor_pos                    Sensor coordinates.
 * @param wall_pos                      Farthest point with no wall coordinates.
 *
 * @return                              True if bottom wall absence detected, false otherwise.
 */
static bool is_wall_bottom_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos);

/**
 * Check if absent wall is right for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param sensor_pos                    Sensor coordinates.
 * @param wall_pos                      Farthest point with no wall coordinates.
 *
 * @return                              True if right wall absence detected, false otherwise.
 */
static bool is_wall_right_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos);

/**
 * Check if absent wall is top for current cell.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 * @param sensor_pos                    Sensor coordinates.
 * @param wall_pos                      Farthest point with no wall coordinates.
 *
 * @return                              True if top wall absence detected, false otherwise.
 */
static bool is_wall_top_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos);

/**
 * Minimum value of coordinate in front of robot.
 *
 * @param cell                          Current cell.
 *
 * @return                              Minimum value of front coordinate.
 */
static float wall_front_min(int32_t cell);

/**
 * Maximum value of coordinate in front of robot.
 *
 * @param cell                          Current cell.
 *
 * @return                              Maximum value of front coordinate.
 */
static float wall_front_max(int32_t cell);

/**
 * Minimum value of coordinate on the side of robot.
 *
 * @param cell                          Current cell.
 *
 * @return                              Minimum value of side coordinate.
 */
static float wall_side_min(int32_t cell);

/**
 * Maximum value of coordinate on the side of robot.
 *
 * @param cell                          Current cell.
 *
 * @return                              Maximum value of side coordinate.
 */
static float wall_side_max(int32_t cell);

/**
 * Calculate cell index from x and y indices.
 *
 * @param cell_x                        Cell index in x axis.
 * @param cell_y                        Cell index in y axis.
 *
 * @return                              Cell index.
 */
PRIVATE int32_t calculate_cell(int32_t cell_x, int32_t cell_y);

/**
 * Calculate cell index in one axis based on value in mm.
 *
 * @param xy                            Coordinate value in millimeters.
 *
 * @return                              Cell index in one axis.
 */
static int32_t calcluate_cell_xy(float xy);

void map_update(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state)
{
    int32_t cell_x;
    int32_t cell_y;

    cell_x = calcluate_cell_xy(sensor_pos->x);
    cell_y = calcluate_cell_xy(sensor_pos->y);

    //todo: what to do when error - cell_xy < 0?

    if (MAP_WALL_PRESENT == wall_state)
    {
        wall_present_add(cell_x, cell_y, wall_pos);
    }
    else if (MAP_WALL_ABSENT == wall_state)
    {
        wall_absent_add(cell_x, cell_y, sensor_pos, wall_pos);
    }
    else
    {
        /* Map presence unknown - don't add. */
    }
}

static void wall_present_add(int32_t cell_x, int32_t cell_y, struct coords *wall_pos)
{
    if (is_wall_left_present(cell_x, cell_y, wall_pos) == true)
    {
        map_validate_wall_left(calculate_cell(cell_x, cell_y), MAP_WALL_PRESENT);
    }
    else if (is_wall_bottom_present(cell_x, cell_y, wall_pos) == true)
    {
        map_validate_wall_bottom(calculate_cell(cell_x, cell_y), MAP_WALL_PRESENT);
    }
    else if (is_wall_right_present(cell_x, cell_y, wall_pos) == true)
    {
        map_validate_wall_right(calculate_cell(cell_x, cell_y), MAP_WALL_PRESENT);
    }
    else if (is_wall_top_present(cell_x, cell_y, wall_pos) == true)
    {
        map_validate_wall_top(calculate_cell(cell_x, cell_y), MAP_WALL_PRESENT);
    }
    else
    {
        /* Wall cannot be added - constraints not meet. */
    }
}

static void wall_absent_add(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos)
{
    if (is_wall_left_absent(cell_x, cell_y, sensor_pos, wall_pos) == true)
    {
        map_validate_wall_left(calculate_cell(cell_x, cell_y), MAP_WALL_ABSENT);
    }
    else if (is_wall_bottom_absent(cell_x, cell_y, sensor_pos, wall_pos) == true)
    {
        map_validate_wall_bottom(calculate_cell(cell_x, cell_y), MAP_WALL_ABSENT);
    }
    else if (is_wall_right_absent(cell_x, cell_y, sensor_pos, wall_pos) == true)
    {
        map_validate_wall_right(calculate_cell(cell_x, cell_y), MAP_WALL_ABSENT);
    }
    else if (is_wall_top_absent(cell_x, cell_y, sensor_pos, wall_pos) == true)
    {
        map_validate_wall_top(calculate_cell(cell_x, cell_y), MAP_WALL_ABSENT);
    }
    else
    {
        /* NoWall cannot be added - constraints not meet. */
    }
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

static bool is_wall_left_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos)
{
    float l_x_min = wall_front_min(cell_x);
    float l_x_max = wall_front_max(cell_x);
    float l_y_min = wall_side_min(cell_y);
    float l_y_max = wall_side_max(cell_y);

    if ((l_x_min > wall_pos->x) && (l_x_max < sensor_pos->x))
    {
        if ((l_y_min < wall_pos->y) && (l_y_min < sensor_pos->y))
        {
            if ((l_y_max > wall_pos->y) && (l_y_max > sensor_pos->y))
            {
                return true;
            }
        }
    }

    return false;
}

static bool is_wall_bottom_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos)
{
    float b_x_min = wall_side_min(cell_x);
    float b_x_max = wall_side_max(cell_x);
    float b_y_min = wall_front_min(cell_y);
    float b_y_max = wall_front_max(cell_y);

    if ((b_y_min > wall_pos->y) && (b_y_max < sensor_pos->y))
    {
        if ((b_x_min < wall_pos->x) && (b_x_min < sensor_pos->x))
        {
            if ((b_x_max > wall_pos->x) && (b_x_max > sensor_pos->x))
            {
                return true;
            }
        }
    }

    return false;
}

static bool is_wall_right_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos)
{
    float r_x_min = wall_front_min(cell_x + 1);
    float r_x_max = wall_front_max(cell_x + 1);
    float r_y_min = wall_side_min(cell_y);
    float r_y_max = wall_side_max(cell_y);

    if ((r_x_min > sensor_pos->x) && (r_x_max < wall_pos->x))
    {
        if ((r_y_min < wall_pos->y) && (r_y_min < sensor_pos->y))
        {
            if ((r_y_max > wall_pos->y) && (r_y_max > sensor_pos->y))
            {
                return true;
            }
        }
    }

    return false;
}

static bool is_wall_top_absent(int32_t cell_x, int32_t cell_y, struct coords *sensor_pos, struct coords *wall_pos)
{
    float t_x_min = wall_side_min(cell_x);
    float t_x_max = wall_side_max(cell_x);
    float t_y_min = wall_front_min(cell_y + 1);
    float t_y_max = wall_front_max(cell_y + 1);

    if ((t_y_min > sensor_pos->y) && (t_y_max < wall_pos->y))
    {
        if ((t_x_min < wall_pos->x) && (t_x_min < sensor_pos->x))
        {
            if ((t_x_max > wall_pos->x) && (t_x_max > sensor_pos->x))
            {
                return true;
            }
        }
    }

    return false;
}

static float wall_front_min(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM - WALL_THRESHOLD;
}

static float wall_front_max(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM + WALL_THRESHOLD;
}

static float wall_side_min(int32_t cell)
{
    return cell * MAP_CELL_WIDTH_MM + CORNER_THRESHOLD;
}

static float wall_side_max(int32_t cell)
{
    return (cell + 1) * MAP_CELL_WIDTH_MM - CORNER_THRESHOLD;
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
