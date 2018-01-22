/*
 * file:	wall_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing wall sensors.
 */

#include "platform_specific.h"

/* Project includes */
#include "wall/wall.h"

#include "wall_test_task.h"

#define WALL_TEST_TASK_STACKSIZE            (configMINIMAL_STACK_SIZE * 4)
#define WALL_TEST_TASK_PRIORITY             (tskIDLE_PRIORITY + 2)

static void wall_test_task(void *params);

void wall_test_task_init(void)
{
    wall_init();

    rtos_task_create(wall_test_task, "wall_test",
                     WALL_TEST_TASK_STACKSIZE, WALL_TEST_TASK_PRIORITY);
}

static void wall_test_task(void *params)
{
    (void) params;

    int32_t front_l;
    int32_t front_r;
    int32_t diag_l;
    int32_t diag_r;
    int32_t side_l;
    int32_t side_r;

    while (1)
    {
        front_l = wall_front_l_dist_mm_get();
        front_r = wall_front_r_dist_mm_get();
        diag_l = wall_diag_l_dist_mm_get();
        diag_r = wall_diag_r_dist_mm_get();
        side_l = wall_side_l_dist_mm_get();
        side_r = wall_side_r_dist_mm_get();

        printf("%d\t%d\t%d\t%d\t%d\t%d\n", front_l, front_r, diag_l, diag_r, side_l, side_r);

        rtos_delay(1000);
    }
}
