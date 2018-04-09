/*
 * file:    solver.h
 * author:  GAndaLF
 * brief:   Module finding path for labirynth map.
 */

#include "platform_specific.h"

#include "map/map.h"

#include "solver.h"

/** No known path to the target. Default cell value. */
#define SOLVER_VAL_MAX      0xFFFFFFFF

/** Single maze cell data. */
struct solver_cell
{
    uint32_t val;       /**! Floodfill value.*/
    int32_t id_next;    /**! Id of the cell that should be visited next. */
};

/** Data describing solver map. */
struct solver_map_data
{
    struct solver_cell map[MAP_SIZE];
};

/** Solver module parameters. */
struct solver_params
{
    struct solver_map_data *map_last;   /** Pointer to last calculated floodfill results. */
    int32_t map_idx_next;               /** Index of map to be used for next calculation. */
    int32_t map_idx_curr;               /** Index of map storing last calculated floodfill results. */
};

/** Solver maze maps. Double buffered to allow simultaneous calculation and usage. */
static struct solver_map_data solver_map[2];
/** Solver module parameters. */
static struct solver_params solver_params;

/**
 * Clear solver map.
 *
 * Set all cells to SOLVER_VAL_MAX.
 *
 * @param map               Solver map to be cleared.
 */
static void solver_map_clear(struct solver_map_data *map_data);

/**
* Set center cells as path search target.
 */
static void solver_target_set_center(struct solver_map_data *map_data);

/**
* Set start cell as path search target.
 */
static void solver_target_set_start(struct solver_map_data *map_data);

/**
 * Calculate paths in labirynth for map with target set.
 *
 * @param map_used          Map for which paths will be calculated.
 */
static void solver_calc_path(struct solver_map_data *map_used);

/**
 * Switch between map buffers.
 */
static void solver_map_switch(void);

/**
 * Get solver map that can be overwritten.
 *
 * @return                  Solver map.
 */
static struct solver_map_data * solver_map_next_get(void);

/**
 * Update cell with new weight value.
 *
 * @param cell_id               Current cell.
 * @param id_to_check           Cell id to check.
 * @param current_cell_val      Weight value of current cell.
 * @param map_used              Map that should be updated.
 */
static void solver_cell_update(int32_t cell_id, int32_t id_to_check, uint32_t current_cell_val, struct solver_map_data *map_used);

/**
 * Get solver cell value from a given map.
 *
 * @param map               Map to be read.
 * @param cell_id           Cell id.
 *
 * @return                  Solver cell value.
 */
static uint32_t solver_map_cell_val_get(struct solver_map_data *map_data, int32_t cell_id);

/**
 * Get id of next cell to be visited from current cell.
 *
 * @param map               Map to be read.
 * @param cell_id           Current cell id.
 *
 * @return                  Id of the cell that should be visited next.
 */
static int32_t solver_map_cell_id_next_get(struct solver_map_data *map_data, int32_t cell_id);
/**
 * Set solver cell value from a given map.
 *
 * @param map               Map to be written.
 * @param cell_id           Cell id.
 * @param val               Value to be written.
 * @param id_next           Id of cell that should be visited next.
 */
static void solver_map_cell_set(struct solver_map_data *map_data, int32_t cell_id, uint32_t val, int32_t id_next);

void solver_init(void)
{
    int32_t i;

    for (i = 0; i < 2; i++)
    {
        solver_map_clear(&solver_map[i]);
    }

    solver_params.map_last = &solver_map[0];
    solver_params.map_idx_curr = 0;
    solver_params.map_idx_next = 1;
}

void solver_calc_path_to_center(void)
{
    struct solver_map_data *map_used;

    map_used = solver_map_next_get();
    solver_map_clear(map_used);
    solver_target_set_center(map_used);

    solver_calc_path(map_used);

    solver_map_switch();
}

void solver_calc_path_to_start(void)
{
    struct solver_map_data *map_used;

    map_used = solver_map_next_get();
    solver_map_clear(map_used);
    solver_target_set_start(map_used);

    solver_calc_path(map_used);

    solver_map_switch();
}

uint32_t solver_cell_val_get(int32_t cell_id)
{
    if ((0 > cell_id) || (MAP_SIZE <= cell_id))
    {
        return SOLVER_VAL_MAX;
    }

    return solver_map_cell_val_get(&solver_map[solver_params.map_idx_curr], cell_id);
}

int32_t solver_cell_id_next_get(int32_t cell_id)
{
    if ((0 > cell_id) || (MAP_SIZE <= cell_id))
    {
        return SOLVER_VAL_MAX;
    }

    return solver_map_cell_id_next_get(&solver_map[solver_params.map_idx_curr], cell_id);
}

static void solver_map_clear(struct solver_map_data *map_data)
{
    int32_t i;

    for (i = 0; i < MAP_SIZE; i++)
    {
        map_data->map[i].val = SOLVER_VAL_MAX;
        map_data->map[i].id_next = -1;
    }
}

static void solver_target_set_center(struct solver_map_data *map_data)
{
    map_data->map[(MAP_HEIGHT / 2 - 1) * MAP_WIDTH  + MAP_WIDTH  / 2 - 1].val = 0;
    map_data->map[(MAP_HEIGHT / 2 - 1) * MAP_WIDTH  + MAP_WIDTH  / 2].val = 0;
    map_data->map[(MAP_HEIGHT / 2) * MAP_WIDTH  + MAP_WIDTH  / 2 - 1].val = 0;
    map_data->map[(MAP_HEIGHT / 2) * MAP_WIDTH  + MAP_WIDTH  / 2].val = 0;
}

static void solver_target_set_start(struct solver_map_data *map_data)
{
    map_data->map[0].val = 0;
}

static void solver_map_switch(void)
{
    solver_params.map_last = &solver_map[solver_params.map_idx_next];
    solver_params.map_idx_curr = solver_params.map_idx_next;
    solver_params.map_idx_next = (solver_params.map_idx_next + 1) & 0x0001;
}

static struct solver_map_data * solver_map_next_get(void)
{
    return &solver_map[solver_params.map_idx_next];
}

static void solver_calc_path(struct solver_map_data *map_used)
{
    int32_t i, j;
    uint32_t current_cell_val;
    int32_t id_to_check;

    /* Longest possible path goes through all cells, otherwise it is endless loop. */
    for (j = 0; j < MAP_SIZE; j++)
    {
        for (i = 0; i < MAP_SIZE; i++)
        {
            current_cell_val = solver_map_cell_val_get(map_used, i);
            if (SOLVER_VAL_MAX == current_cell_val)
            {
                continue;
            }

            /* Check bottom cell */
            if (MAP_WALL_PRESENT != map_wall_bottom_get(i))
            {
                id_to_check = i - MAP_WIDTH;
                if (id_to_check >= 0)
                {
                    solver_cell_update(i, id_to_check, current_cell_val, map_used);
                }
            }

            /* Check top cell */
            if (MAP_WALL_PRESENT != map_wall_top_get(i))
            {
                id_to_check = i + MAP_WIDTH;
                if (id_to_check < MAP_SIZE)
                {
                    solver_cell_update(i, id_to_check, current_cell_val, map_used);
                }
            }

            /* Check left cell */
            if (MAP_WALL_PRESENT != map_wall_left_get(i))
            {
                id_to_check = i - 1;
                if (id_to_check >= 0)
                {
                    solver_cell_update(i, id_to_check, current_cell_val, map_used);
                }
            }

            /* Check right cell */
            if (MAP_WALL_PRESENT != map_wall_right_get(i))
            {
                id_to_check = i + 1;
                if (id_to_check < MAP_SIZE)
                {
                    solver_cell_update(i, id_to_check, current_cell_val, map_used);
                }
            }
        }
    }
}

static void solver_cell_update(int32_t cell_id, int32_t id_to_check, uint32_t current_cell_val, struct solver_map_data *map_used)
{
    if (current_cell_val < solver_map_cell_val_get(map_used, id_to_check))
    {
        solver_map_cell_set(map_used, id_to_check, current_cell_val + 1, cell_id);
    }
}

static uint32_t solver_map_cell_val_get(struct solver_map_data *map_data, int32_t cell_id)
{
    return map_data->map[cell_id].val;
}

static int32_t solver_map_cell_id_next_get(struct solver_map_data *map_data, int32_t cell_id)
{
    return map_data->map[cell_id].id_next;
}

static void solver_map_cell_set(struct solver_map_data *map_data, int32_t cell_id, uint32_t val, int32_t id_next)
{
    map_data->map[cell_id].val = val;
    map_data->map[cell_id].id_next = id_next;
}
