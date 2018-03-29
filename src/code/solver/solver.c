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
};

/** Solver module parameters. */
struct solver_params
{
    struct solver_cell *map_last;   /** Pointer to last calculated floodfill results. */
    int32_t map_idx_next;           /** Index of map to be used for next calculation. */
    int32_t map_idx_curr;           /** Index of map storing last calculated floodfill results. */
};

/** Solver maze maps. Double buffered to allow simultaneous calculation and usage. */
static struct solver_cell solver_map[2][MAP_SIZE];
/** Solver module parameters. */
static struct solver_params solver_params;

/**
 * Write default values to solver map.
 *
 * Center cells set to 0, all other cells set to SOLVER_VAL_MAX.
 *
 * @param map               Solver map to be cleared.
 */
static void solver_map_clear(struct solver_cell *map);

/**
 * Switch between map buffers.
 */
static void solver_map_switch(void);

/**
 * Get solver map that can be overwritten.
 *
 * @return                  Solver map.
 */
static struct solver_cell * solver_map_next_get(void);

/**
 * Get solver cell value from a given map.
 *
 * @param map               Map to be read.
 * @param cell_id           Cell id.
 *
 * @return                  Solver cell value.
 */
static uint32_t solver_map_cell_val_get(struct solver_cell *map, int32_t cell_id);

/**
 * Set solver cell value from a given map.
 *
 * @param map               Map to be written.
 * @param cell_id           Cell id.
 * @param val               Value to be written.
 */
static void solver_map_cell_val_set(struct solver_cell *map, int32_t cell_id, uint32_t val);

void solver_init(void)
{
    int32_t i;

    for (i = 0; i < 2; i++)
    {
        solver_map_clear(solver_map[i]);
    }

    solver_params.map_last = solver_map[0];
    solver_params.map_idx_curr = 0;
    solver_params.map_idx_next = 1;
}

void solver_path_calc(void)
{
    int32_t i, j;
    struct solver_cell *map_used;
    uint32_t current_cell_val;
    uint32_t new_cell_val;
    int32_t id_to_check;

    map_used = solver_map_next_get();
    solver_map_clear(map_used);

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

            new_cell_val = current_cell_val + 1;

            /* Check bottom cell */
            if (MAP_WALL_PRESENT != map_wall_bottom_get(i))
            {
                id_to_check = i - MAP_WIDTH;
                if (id_to_check >= 0)
                {
                    if (current_cell_val < solver_map_cell_val_get(map_used, id_to_check))
                    {
                        solver_map_cell_val_set(map_used, id_to_check, new_cell_val);
                    }
                }
            }

            /* Check top cell */
            if (MAP_WALL_PRESENT != map_wall_top_get(i))
            {
                id_to_check = i + MAP_WIDTH;
                if (id_to_check < MAP_SIZE)
                {
                    if (current_cell_val < solver_map_cell_val_get(map_used, id_to_check))
                    {
                        solver_map_cell_val_set(map_used, id_to_check, new_cell_val);
                    }
                }
            }

            /* Check left cell */
            if (MAP_WALL_PRESENT != map_wall_left_get(i))
            {
                id_to_check = i - 1;
                if (id_to_check >= 0)
                {
                    if (current_cell_val < solver_map_cell_val_get(map_used, id_to_check))
                    {
                        solver_map_cell_val_set(map_used, id_to_check, new_cell_val);
                    }
                }
            }

            /* Check right cell */
            if (MAP_WALL_PRESENT != map_wall_right_get(i))
            {
                id_to_check = i + 1;
                if (id_to_check < MAP_SIZE)
                {
                    if (current_cell_val < solver_map_cell_val_get(map_used, id_to_check))
                    {
                        solver_map_cell_val_set(map_used, id_to_check, new_cell_val);
                    }
                }
            }
        }
    }

    solver_map_switch();
}

uint32_t solver_cell_val_get(int32_t cell_id)
{
    if ((0 > cell_id) || (MAP_SIZE <= cell_id))
    {
        return SOLVER_VAL_MAX;
    }

    return solver_map_cell_val_get(solver_map[solver_params.map_idx_curr], cell_id);
}

static void solver_map_clear(struct solver_cell *map)
{
    int32_t i;

    for (i = 0; i < MAP_SIZE; i++)
    {
        map[i].val = SOLVER_VAL_MAX;
    }

    /* Set maze center as target */
    map[(MAP_HEIGHT / 2 - 1) * MAP_WIDTH  + MAP_WIDTH  / 2 - 1].val = 0;
    map[(MAP_HEIGHT / 2 - 1) * MAP_WIDTH  + MAP_WIDTH  / 2].val = 0;
    map[(MAP_HEIGHT / 2) * MAP_WIDTH  + MAP_WIDTH  / 2 - 1].val = 0;
    map[(MAP_HEIGHT / 2) * MAP_WIDTH  + MAP_WIDTH  / 2].val = 0;
}

static void solver_map_switch(void)
{
    solver_params.map_last = solver_map[solver_params.map_idx_next];
    solver_params.map_idx_curr = solver_params.map_idx_next;
    solver_params.map_idx_next = (solver_params.map_idx_next + 1) & 0x0001;
}

static struct solver_cell * solver_map_next_get(void)
{
    return solver_map[solver_params.map_idx_next];
}

static uint32_t solver_map_cell_val_get(struct solver_cell *map, int32_t cell_id)
{
    return map[cell_id].val;
}

static void solver_map_cell_val_set(struct solver_cell *map, int32_t cell_id, uint32_t val)
{
    map[cell_id].val = val;
}
