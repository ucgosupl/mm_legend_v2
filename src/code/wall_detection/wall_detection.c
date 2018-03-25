/*
 * file:	wall_detection.c
 * author:	GAndaLF
 * brief:	Wall detection based on current position and wall sensors.
 */

#include "platform_specific.h"
#include <math.h>

#include "map/map.h"
#include "position/position.h"
#include "wall_sensor/wall_sensor.h"
#include "wall_sensor/wall_sensor_offsets.h"

#include "wall_detection.h"

#define NO_WALL_THRESHOLD       130

static struct coords sensor_offsets[WALL_SENSOR_CNT] =
{
        /** FRONT_R */
        {WALL_SENSOR_FRONT_OFFSET_X, -WALL_SENSOR_FRONT_OFFSET_Y, WALL_SENSOR_FRONT_OFFSET_A},
        /** SIDE_L */
        {WALL_SENSOR_SIDE_OFFSET_X, WALL_SENSOR_SIDE_OFFSET_Y, WALL_SENSOR_SIDE_OFFSET_A},
        /** DIAG_R */
        {WALL_SENSOR_DIAG_OFFSET_X, -WALL_SENSOR_DIAG_OFFSET_Y, -WALL_SENSOR_DIAG_OFFSET_A},
        /** FRONT_L */
        {WALL_SENSOR_FRONT_OFFSET_X, WALL_SENSOR_FRONT_OFFSET_Y, WALL_SENSOR_FRONT_OFFSET_A},
        /** SIDE_R */
        {WALL_SENSOR_SIDE_OFFSET_X, -WALL_SENSOR_SIDE_OFFSET_Y, -WALL_SENSOR_SIDE_OFFSET_A},
        /** DIAG_L */
        {WALL_SENSOR_DIAG_OFFSET_X, WALL_SENSOR_DIAG_OFFSET_Y, WALL_SENSOR_DIAG_OFFSET_A},
};

static int32_t calculate_cell(int32_t x, int32_t y);
PRIVATE void update_wall_with_sensor(struct coords *robot_pos, int32_t sensor_id, int32_t sensor_data);
static void calculate_sensor_pos(struct coords *robot_pos, int32_t sensor_id, struct coords *sensor_pos);
PRIVATE map_wall_state_t calculate_wall_pos(struct coords *sensor_pos, int32_t sensor_data, struct coords *wall_pos);

void wall_detection(void)
{
    int32_t i;

    int32_t sensor_data[WALL_SENSOR_CNT];

    struct coords robot_pos;

    /* Get current position. */
    robot_pos.x = position_x_get();
    robot_pos.y = position_y_get();
    robot_pos.alpha = position_alpha_get();

    /* Get all sensor readings at once. */
    for (i = 0; i < WALL_SENSOR_CNT; i++)
    {
        sensor_data[i] = wall_sensor_dist_mm_get(i);
    }

    for (i = 0; i < WALL_SENSOR_CNT; i++)
    {
        update_wall_with_sensor(&robot_pos, i, sensor_data[i]);
    }

    //todo: this line stays for now only to pass initial tests. Remove when final solution is ready.
    int32_t cell_id;
    cell_id = calculate_cell(robot_pos.x, robot_pos.y);
    if (0 > cell_id)
    {
        //todo: handle error
        return;
    }
    map_wall_left_get(cell_id);
}

PRIVATE void update_wall_with_sensor(struct coords *robot_pos, int32_t sensor_id, int32_t sensor_data)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    map_wall_state_t wall_state = MAP_WALL_UNKNOWN;

    calculate_sensor_pos(robot_pos, sensor_id, &sensor_pos);
    wall_state = calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    /* Update map with detected wall. */
    if (MAP_WALL_UNKNOWN != wall_state)
    {
        map_update(&sensor_pos, &wall_pos, wall_state);
    }
}

static int32_t calculate_cell(int32_t x, int32_t y)
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

static void calculate_sensor_pos(struct coords *robot_pos, int32_t sensor_id, struct coords *sensor_pos)
{
    sensor_pos->x = robot_pos->x + sensor_offsets[sensor_id].x;
    sensor_pos->y = robot_pos->y + sensor_offsets[sensor_id].y;
    sensor_pos->alpha = robot_pos->alpha + sensor_offsets[sensor_id].alpha;
}

PRIVATE map_wall_state_t calculate_wall_pos(struct coords *sensor_pos, int32_t sensor_data, struct coords *wall_pos)
{
    float sensor_after_threshold;
    map_wall_state_t wall_state = MAP_WALL_UNKNOWN;

    if (WALL_TOO_CLOSE == sensor_data)
    {
        /*
         * If wall is too close, distance data are not reliable. We can assume
         * that wall is present, but distance calculations would be tricky.
         * Now we assume that wall is already detected before robot is too close.
         */
        sensor_after_threshold = 0.0f;
        wall_state = MAP_WALL_UNKNOWN;
    }
    else if (NO_WALL_THRESHOLD < sensor_data)
    {
        sensor_after_threshold = (float)NO_WALL_THRESHOLD;
        wall_state = MAP_WALL_ABSENT;
    }
    else
    {
        sensor_after_threshold = (float)sensor_data;
        wall_state = MAP_WALL_PRESENT;
    }

    wall_pos->x = sensor_pos->x + sensor_after_threshold * cosf(sensor_pos->alpha);
    wall_pos->y = sensor_pos->y + sensor_after_threshold * sinf(sensor_pos->alpha);
    wall_pos->alpha = 0;

    return wall_state;
}
