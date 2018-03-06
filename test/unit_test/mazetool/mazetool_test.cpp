#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C" {
#include "map/map.h"
#include "solver/solver.h"
}

#define RIGHT           0x01
#define BOTTOM          0x02
#define LEFT            0x04
#define TOP             0x08

#define PRINT_WALL_VERTICAL()           printf("---")
#define PRINT_NO_WALL_VERTICAL()        printf("   ")
#define PRINT_WALL_LEFT()               printf("|   ")
#define PRINT_NO_WALL_LEFT()            printf("    ")
#define PRINT_WALL_RIGHT()              printf("|")
#define PRINT_NO_WALL_RIGHT()           printf(" ")
#define PRINT_WALL_POST()               printf("o")

extern int apec2017_maz[];

static void print_unsolved(int *maze);
static void load_map(int *maze);
static void print_map(void);
static void print_floodfill(void);

TEST_GROUP(mazetool)
{
    void setup()
    {
        map_init();
        solver_init();
    }

    void teardown()
    {
    }
};

TEST(mazetool, FirstTest)
{
    print_unsolved(apec2017_maz);
    load_map(apec2017_maz);
    print_map();
    solver_path_calc();
    print_floodfill();

   FAIL("Fail me!");
}

static void print_unsolved(int *maze)
{
    int32_t i, j;

    printf("Maze layout:\n");

    for (j = 0; j < MAP_HEIGHT; j++)
    {
        for (i = 0; i < MAP_WIDTH; i++)
        {
            PRINT_WALL_POST();

            if (0 != (TOP & maze[j * MAP_WIDTH + i]))
            {
                PRINT_WALL_VERTICAL();
            }
            else
            {
                PRINT_NO_WALL_VERTICAL();
            }

            PRINT_WALL_POST();
        }

        printf("\n");

        for (i = 0; i < MAP_WIDTH; i++)
        {
            if (0 != (LEFT & maze[j * MAP_WIDTH + i]))
            {
                PRINT_WALL_LEFT() ;
            }
            else
            {
                PRINT_NO_WALL_LEFT();
            }

            if (0 != (RIGHT & maze[j * MAP_WIDTH + i]))
            {
                PRINT_WALL_RIGHT();
            }
            else
            {
                PRINT_NO_WALL_RIGHT();
            }
        }

        printf("\n");

        for (i = 0; i < MAP_WIDTH; i++)
        {
            PRINT_WALL_POST();

            if (0 != (BOTTOM & maze[j * MAP_WIDTH + i]))
            {
                PRINT_WALL_VERTICAL();
            }
            else
            {
                PRINT_NO_WALL_VERTICAL();
            }

            PRINT_WALL_POST();
        }

        printf("\n");
    }

    printf("\n");
}

static void load_map(int *maze)
{
    int32_t i;

    for (i = 0; i < MAP_SIZE; i++)
    {
        if (0 != (RIGHT & maze[i]))
        {
            map_add_right_wall(i);
        }
        else
        {
            map_add_right_no_wall(i);
        }

        if (0 != (BOTTOM & maze[i]))
        {
            map_add_bottom_wall(i);
        }
        else
        {
            map_add_bottom_no_wall(i);
        }

        if (0 != (LEFT & maze[i]))
        {
            map_add_left_wall(i);
        }
        else
        {
            map_add_left_no_wall(i);
        }

        if (0 != (TOP & maze[i]))
        {
            map_add_top_wall(i);
        }
        else
        {
            map_add_top_no_wall(i);
        }
    }
}

static void print_map(void)
{
    int32_t i, j;

    printf("Maze map:\n");

    for (j = 0; j < MAP_HEIGHT; j++)
    {
        for (i = 0; i < MAP_WIDTH; i++)
        {
            PRINT_WALL_POST();

            if (MAP_WALL_PRESENT == (map_wall_top_get(j * MAP_WIDTH + i)))
            {
                PRINT_WALL_VERTICAL();
            }
            else
            {
                PRINT_NO_WALL_VERTICAL();
            }

            PRINT_WALL_POST();
        }

        printf("\n");

        for (i = 0; i < MAP_WIDTH; i++)
        {
            if (MAP_WALL_PRESENT == (map_wall_left_get(j * MAP_WIDTH + i)))
            {
                PRINT_WALL_LEFT();
            }
            else
            {
                PRINT_NO_WALL_LEFT();
            }

            if (MAP_WALL_PRESENT == (map_wall_right_get(j * MAP_WIDTH + i)))
            {
                PRINT_WALL_RIGHT();
            }
            else
            {
                PRINT_NO_WALL_RIGHT();
            }
        }

        printf("\n");

        for (i = 0; i < MAP_WIDTH; i++)
        {
            PRINT_WALL_POST();

            if (MAP_WALL_PRESENT == (map_wall_bottom_get(j * MAP_WIDTH + i)))
            {
                PRINT_WALL_VERTICAL();
            }
            else
            {
                PRINT_NO_WALL_VERTICAL();
            }

            PRINT_WALL_POST();
        }

        printf("\n");
    }

    printf("\n");
}

static void print_floodfill(void)
{
    int32_t i, j;

    printf("Floodfill values:\n");

    for (j = 0; j < MAP_HEIGHT; j++)
    {
        for (i = 0; i < MAP_WIDTH; i++)
        {
            printf(" %3u ", solver_cell_val_get(j * MAP_WIDTH + i));
        }

        printf("\n");
    }

    printf("\n");
}
