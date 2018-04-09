/*
 * file:    map.c
 * author:  GAndaLF
 * brief:   Labirynth map layout manager.
 */

#include "platform_specific.h"

#include "map.h"
#include "map_internal.h"

/** State of a single cell in labirynth map. */
struct map_cell
{
    map_wall_state_t left;      /**< State of the left wall. */
    map_wall_state_t right;     /**< State of the right wall. */
    map_wall_state_t top;       /**< State of the top wall. */
    map_wall_state_t bottom;    /**< State of the bottom wall. */
};

/** Labirynth map containing all cells. */
static struct map_cell labirynth_map[MAP_SIZE];

/**
 * Update state of the left wall for a given cell id.
 *
 * @param cell_id           Cell id to be updated.
 * @param state             New wall state.
 */
static void add_left(int32_t cell_id, map_wall_state_t state);

/**
 * Update state of the right wall for a given cell id.
 *
 * @param cell_id           Cell id to be updated.
 * @param state             New wall state.
 */
static void add_right(int32_t cell_id, map_wall_state_t state);

/**
 * Update state of the top wall for a given cell id.
 *
 * @param cell_id           Cell id to be updated.
 * @param state             New wall state.
 */
static void add_top(int32_t cell_id, map_wall_state_t state);

/**
 * Update state of the bottom wall for a given cell id.
 *
 * @param cell_id           Cell id to be updated.
 * @param state             New wall state.
 */
static void add_bottom(int32_t cell_id, map_wall_state_t state);

/**
 * Check if cell id is out of labirynth map array bounds.
 *
 * @param cell_id           Cell id to be checked.
 *
 * @return                  0 on success, -1 on error.
 */
static int32_t array_bounds_check(int32_t cell_id);

void map_init(void)
{
    int32_t i;

    for (i = 0; i < MAP_SIZE; i++)
    {
        labirynth_map[i].left = MAP_WALL_UNKNOWN;
        labirynth_map[i].right = MAP_WALL_UNKNOWN;
        labirynth_map[i].top = MAP_WALL_UNKNOWN;
        labirynth_map[i].bottom = MAP_WALL_UNKNOWN;

        /* Labirynth is surrounded by walls. */
        if (0 == i % MAP_WIDTH)
        {
            labirynth_map[i].left = MAP_WALL_PRESENT;
        }

        if ((MAP_WIDTH - 1) == i % MAP_WIDTH)
        {
            labirynth_map[i].right = MAP_WALL_PRESENT;
        }

        if (i < MAP_WIDTH)
        {
            labirynth_map[i].bottom = MAP_WALL_PRESENT;
        }

        if (i >= MAP_SIZE - MAP_WIDTH)
        {
            labirynth_map[i].top = MAP_WALL_PRESENT;
        }
    }

    /* In start cell there is only one exit. */
    map_add_right_no_wall(0);
    map_add_top_wall(0);

    /* Center 4 cells are a square with no walls inside */
    map_add_right_no_wall((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2 - 1);
    map_add_top_no_wall((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2 - 1);
    map_add_left_no_wall(MAP_HEIGHT/2 * MAP_WIDTH + MAP_WIDTH/2);
    map_add_bottom_no_wall(MAP_HEIGHT/2 * MAP_WIDTH + MAP_WIDTH/2);
}

map_wall_state_t map_wall_left_get(int32_t cell_id)
{
    if (0 > array_bounds_check(cell_id))
    {
        return MAP_WALL_ERROR;
    }

    return labirynth_map[cell_id].left;
}

map_wall_state_t map_wall_right_get(int32_t cell_id)
{
    if (0 > array_bounds_check(cell_id))
    {
        return MAP_WALL_ERROR;
    }

    return labirynth_map[cell_id].right;
}

map_wall_state_t map_wall_top_get(int32_t cell_id)
{
    if (0 > array_bounds_check(cell_id))
    {
        return MAP_WALL_ERROR;
    }

    return labirynth_map[cell_id].top;
}

map_wall_state_t map_wall_bottom_get(int32_t cell_id)
{
    if (0 > array_bounds_check(cell_id))
    {
        return MAP_WALL_ERROR;
    }

    return labirynth_map[cell_id].bottom;
}

void map_add_left_no_wall(int32_t cell_id)
{
    add_left(cell_id, MAP_WALL_ABSENT);
}

void map_add_right_no_wall(int32_t cell_id)
{
    add_right(cell_id, MAP_WALL_ABSENT);
}

void map_add_top_no_wall(int32_t cell_id)
{
    add_top(cell_id, MAP_WALL_ABSENT);
}

void map_add_bottom_no_wall(int32_t cell_id)
{
    add_bottom(cell_id, MAP_WALL_ABSENT);
}

void map_add_left_wall(int32_t cell_id)
{
    add_left(cell_id, MAP_WALL_PRESENT);
}

void map_add_right_wall(int32_t cell_id)
{
    add_right(cell_id, MAP_WALL_PRESENT);
}

void map_add_top_wall(int32_t cell_id)
{
    add_top(cell_id, MAP_WALL_PRESENT);
}

void map_add_bottom_wall(int32_t cell_id)
{
    add_bottom(cell_id, MAP_WALL_PRESENT);
}

static void add_left(int32_t cell_id, map_wall_state_t state)
{
    int32_t cell_adjacent;

    if (0 > array_bounds_check(cell_id))
    {
        return;
    }

    /* Allow only one update of wall state */
    if (MAP_WALL_UNKNOWN != labirynth_map[cell_id].left)
    {
        //TODO: count occurences of double wall update
        return;
    }

    labirynth_map[cell_id].left = state;

    cell_adjacent = map_cell_adjacent_to_wall_left_get(cell_id);
    if (0 <= cell_adjacent)
    {
        labirynth_map[cell_adjacent].right = state;
    }
}

static void add_right(int32_t cell_id, map_wall_state_t state)
{
    int32_t cell_adjacent;

    if (0 > array_bounds_check(cell_id))
    {
        return;
    }

    /* Allow only one update of wall state */
    if (MAP_WALL_UNKNOWN != labirynth_map[cell_id].right)
    {
        //TODO: count occurences of double wall update
        return;
    }

    labirynth_map[cell_id].right = state;

    cell_adjacent = map_cell_adjacent_to_wall_right_get(cell_id);
    if (0 <= cell_adjacent)
    {
        labirynth_map[cell_adjacent].left = state;
    }
}

static void add_top(int32_t cell_id, map_wall_state_t state)
{
    int32_t cell_adjacent;

    if (0 > array_bounds_check(cell_id))
    {
        return;
    }

    /* Allow only one update of wall state */
    if (MAP_WALL_UNKNOWN != labirynth_map[cell_id].top)
    {
        //TODO: count occurences of double wall update
        return;
    }

    labirynth_map[cell_id].top = state;

    cell_adjacent = map_cell_adjacent_to_wall_top_get(cell_id);
    if (0 <= cell_adjacent)
    {
        labirynth_map[cell_adjacent].bottom = state;
    }
}

static void add_bottom(int32_t cell_id, map_wall_state_t state)
{
    int32_t cell_adjacent;

    if (0 > array_bounds_check(cell_id))
    {
        return;
    }

    /* Allow only one update of wall state */
    if (MAP_WALL_UNKNOWN != labirynth_map[cell_id].bottom)
    {
        //TODO: count occurences of double wall update
        return;
    }

    labirynth_map[cell_id].bottom = state;

    cell_adjacent = map_cell_adjacent_to_wall_bottom_get(cell_id);
    if (0 <= cell_adjacent)
    {
        labirynth_map[cell_adjacent].top = state;
    }
}

static int32_t array_bounds_check(int32_t cell_id)
{
    if ((0 > cell_id) || (MAP_SIZE <= cell_id))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
