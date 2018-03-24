/*
 * file:	wall_detection.c
 * author:	GAndaLF
 * brief:	Wall detection based on current position and wall sensors.
 */

#include "platform_specific.h"

#include "map/map.h"
#include "position/position.h"
#include "wall_sensor/wall_sensor.h"

#include "wall_detection.h"

static int32_t calculate_cell(int32_t x, int32_t y);

void wall_detection(void)
{
    float pos_x;
    float pos_y;
    //float pos_alpha;

    int32_t cell_id;

    //int32_t sensor_front_l;
    //int32_t sensor_front_r;
    //int32_t sensor_diag_l;
    //int32_t sensor_diag_r;
    //int32_t sensor_side_l;
    //int32_t sensor_side_r;

    //get position
    pos_x = position_x_get();
    pos_y = position_y_get();
    //pos_alpha = position_alpha_get();

    cell_id = calculate_cell(pos_x, pos_y);
    if (0 > cell_id)
    {
        //todo: handle error
        return;
    }

    //get sensor readings
    //sensor_front_l = wall_sensor_front_l_dist_mm_get();
    //sensor_front_r = wall_sensor_front_r_dist_mm_get();
    //sensor_diag_l = wall_sensor_diag_l_dist_mm_get();
    //sensor_diag_r = wall_sensor_diag_r_dist_mm_get();
    //sensor_side_l = wall_sensor_side_l_dist_mm_get();
    //sensor_side_r = wall_sensor_side_r_dist_mm_get();

    //find existing/not existing walls
    map_wall_left_get(cell_id);
}

static int32_t calculate_cell(int32_t x, int32_t y)
{
    int32_t cell_x;
    int32_t cell_y;

    if (x >= MAP_WIDTH * CELL_WIDTH_MM)
    {
        return -1;
    }

    if (y >= MAP_WIDTH * CELL_WIDTH_MM)
    {
        return -1;
    }

    cell_x = x / CELL_WIDTH_MM;
    cell_y = y / CELL_WIDTH_MM;

    return cell_x + MAP_WIDTH * cell_y;
}
